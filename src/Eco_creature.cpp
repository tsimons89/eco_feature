#include "Eco_creature.hpp"
#include "Eco_filter.hpp"

int Eco_creature::num_trees;
int Eco_creature::max_tree_depth;

Eco_creature::Eco_creature(string genome_str,double alpha,string forest_path){
	this->alpha = alpha;
	genome = Eco_genome(genome_str);
	load_forest(forest_path);
}


int Eco_creature::predict(Mat image){
	Mat processed = process(vector<Mat>{image});
	Mat results;
	forest->predict(processed, results);
	return (int)results.at<float>(0,0);
}


void Eco_creature::train(Data_set data_set){
	if(trained)
		return;
	set_labels_and_images(data_set);
	init_forest();
	forest->train(images, ml::ROW_SAMPLE, labels);
	fitness = NOT_UPDATED;
	weighted_fitness = NOT_UPDATED;
	trained = true;
}

void Eco_creature::set_labels_and_images(Data_set data_set){
	labels = Mat(data_set.get_labels(),true);
	images = process(data_set.get_images());
}

Mat Eco_creature::process(vector<Mat> images){
	Eco_filter filter(genome);
	Mat filtered_set = filter.apply(images);
	return filtered_set.reshape(0,images.size());
}

void Eco_creature::init_forest(){
	forest = RTrees::create();
	forest->setMaxDepth(Eco_creature::max_tree_depth);//15
    forest->setMinSampleCount(MIN_SAMPLE_COUNT);
    forest->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, Eco_creature::num_trees, 0));
}

void Eco_creature::update_fitness(Data_set data_set){
	assert(trained);
	if(fitness == NOT_UPDATED)
		set_fitness(data_set);
}

void Eco_creature::update_weighted_fitness(Data_set data_set){
	assert(trained);
	if(weighted_fitness == NOT_UPDATED){
		set_weighted_fitness(data_set);
		set_alpha(data_set);
	}
}

void Eco_creature::set_weighted_fitness(Data_set data_set){
	set_labels_and_images(data_set);
	Mat results = predict();
	weighted_fitness = calc_weighted_fitness(results,data_set.get_weights());
}

void Eco_creature::set_alpha(Data_set data_set){
	alpha = log(weighted_fitness/(1-weighted_fitness)) + log(data_set.get_num_labels()-1);
}



void Eco_creature::set_fitness(Data_set data_set){
	set_labels_and_images(data_set);
	Mat results = predict();
	fitness = calc_fitness(results);
	assert(fitness != NOT_UPDATED);
}

Mat Eco_creature::predict(){
	assert(images.rows > 0 && trained);
	Mat results;
	forest->predict(images, results);
	return results;
}

double Eco_creature::calc_fitness(Mat results){
	assert(results.total() == labels.total());
	int num_correct = 0;
	for(unsigned int i = 0; i < results.total(); i++){
		if((int)results.at<float>(i,0) == labels.at<int>(i,0))
			num_correct++;
	}
	return (double)num_correct/(double)results.total();
}

double Eco_creature::calc_weighted_fitness(Mat results,vector<double> weights){
	assert(results.total() == labels.total());
	double score = 0,total = 0;
	for(unsigned int i = 0; i < results.total(); i++){
		if((int)results.at<float>(i,0) == labels.at<int>(i,0))
			score+=weights.at(i);
		total+=weights.at(i);
	}
	return score/total;
}


bool Eco_creature::operator<(const Eco_creature& rhs){
	if(fitness == rhs.fitness)
		return genome.get_total() < rhs.genome.get_total();
	return fitness < rhs.fitness;
}

ostream& operator<<(ostream& stream, const Eco_creature& eco_creature){
	stream << eco_creature.genome; 
	return stream;
}

void Eco_creature::write_forest(string path){
	stringstream filename;
	filename << path << "/rf_" << genome << ".yml";
	forest.get()->save(filename.str());
}

void Eco_creature::load_forest(string path){
	stringstream filename;
	filename << path << "/rf_" << genome << ".yml";
	forest = RTrees::load(filename.str());
}



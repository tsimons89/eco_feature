#include "Creature.hpp"
#include "Filter.hpp"
#include <ctime>

int Creature::num_trees;
int Creature::max_tree_depth;

Creature::Creature(string genome_str,double alpha,string forest_path){
	this->alpha = alpha;
	genome = Genome(genome_str);
	load_forest(forest_path);
}

Creature::Creature(string genome_str){
	genome = Genome(genome_str);
}

Creature::Creature(int x_blur,int y_blur, int x_diff, int y_diff){
	genome = Genome(x_blur,y_blur,x_diff,y_diff);
}

int Creature::predict(Mat image){
	Mat processed = process(vector<Mat>{image});
	Mat results;
	forest->predict(processed, results);
	return (int)results.at<float>(0,0);
}

void Creature::train(Data_set data_set){
	if(trained)
		return;
	set_labels_and_images(data_set);
	init_forest();
	forest->train(images, ml::ROW_SAMPLE, labels);
	fitness = NOT_UPDATED;
	weighted_fitness = NOT_UPDATED;
	trained = true;
}

void Creature::set_labels_and_images(Data_set data_set){
	labels = Mat(data_set.get_labels(), true);
	images = process(data_set.get_images());
}

Mat Creature::process(vector<Mat> images){
	Filter filter(genome);
	Mat filtered_set = filter.apply(images);
	return filtered_set.reshape(0,images.size());
}

void Creature::init_forest(){
	forest = RTrees::create();
	forest->setMaxDepth(max_tree_depth);
    forest->setMinSampleCount(MIN_SAMPLE_COUNT);
    forest->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, num_trees, 0));
}

void Creature::update_fitness(Data_set data_set){
	assert(trained);
	if(fitness == NOT_UPDATED)
		set_fitness(data_set);
}

void Creature::update_weighted_fitness(Data_set data_set){
	assert(trained);
	if(weighted_fitness == NOT_UPDATED){
		set_weighted_fitness(data_set);
		set_alpha(data_set);
	}
}

void Creature::set_weighted_fitness(Data_set data_set){
	set_labels_and_images(data_set);
	Mat results = predict();
	weighted_fitness = calc_weighted_fitness(results,data_set.get_weights());
}

void Creature::set_alpha(Data_set data_set){
	if(weighted_fitness == 1)
		alpha = 100;
	else
		alpha = log(weighted_fitness/(1-weighted_fitness)) + log(data_set.get_num_labels()-1);
}



void Creature::set_fitness(Data_set data_set){
	set_labels_and_images(data_set);
	Mat results = predict();
	fitness = calc_fitness(results);
	assert(fitness != NOT_UPDATED);
}

Mat Creature::predict(){
	assert(images.rows > 0 && trained);
	Mat results;
	forest->predict(images, results);
	return results;
}

double Creature::calc_fitness(Mat results){
	assert(results.total() == labels.total());
	int num_correct = 0;
	for(unsigned int i = 0; i < results.total(); i++){
		if((int)results.at<float>(i,0) == labels.at<int>(i,0))
			num_correct++;
	}
	return (double)num_correct/(double)results.total();
}

double Creature::calc_weighted_fitness(Mat results,vector<double> weights){
	assert(results.total() == labels.total());
	double score = 0,total = 0;
	for(unsigned int i = 0; i < results.total(); i++){
		if((int)results.at<float>(i,0) == labels.at<int>(i,0))
			score+=weights.at(i);
		total+=weights.at(i);
	}
	return score/total;
}

bool Creature::operator<(const Creature& rhs){
	if(weighted_fitness == rhs.weighted_fitness)
		return genome.get_total() < rhs.genome.get_total();
	return weighted_fitness < rhs.weighted_fitness;
}

ostream& operator<<(ostream& stream, const Creature& eco_creature){
	stream << eco_creature.genome; 
	return stream;
}

void Creature::write_forest(string path){
	stringstream filename;
	filename << path << "/rf_" << genome << ".yml";
	forest.get()->save(filename.str());
}

void Creature::load_forest(string path){
	stringstream filename;
	filename << path << "/rf_" << genome << ".yml";
	forest = RTrees::load(filename.str());
}



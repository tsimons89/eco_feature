#include "Adaboost_model.hpp"
#include <ctime>

int unsigned Adaboost_model::num_creatures = 0;
int unsigned Adaboost_model::pool_size = 0;
string Adaboost_model::results_path;

void Adaboost_model::train(){
	check_params();
	train_data.load_data();
	model_creatures.clear();
	while(model_creatures.size() < num_creatures)
		add_creature_to_model();
}

void Adaboost_model::add_creature_to_model(){
	set_resampled_data();
	pool_creatures.clear();
	for(unsigned int i = 0; i < Adaboost_model::pool_size; i++)
		add_creature_to_pool();
	update_model();
}

void Adaboost_model::set_resampled_data(){
	if(model_creatures.size() == 0)
		resample_data = train_data;
	else
		resample_data = train_data.resample();
}
void Adaboost_model::check_params(){
	assert(Adaboost_model::num_creatures != 0);
	assert(Adaboost_model::pool_size != 0);
}

void Adaboost_model::add_creature_to_pool(){
	Eco_population pop;
	pool_creatures.push_back(pop.create_fit_creature(resample_data));
}

void Adaboost_model::update_model(){
	Eco_creature best_pool_creature = select_from_pool();
	if(!is_creature_in_model(best_pool_creature)){
		cout << "Creature " << model_creatures.size() << " of " << num_creatures << endl;
		update_weights(best_pool_creature);
		model_creatures.push_back(best_pool_creature);
	}
}

Eco_creature Adaboost_model::select_from_pool(){
	Eco_creature fittest_creature;
	for(auto& creature:pool_creatures){
		creature.update_weighted_fitness(train_data);
		fittest_creature = (creature.get_weighted_fitness() > fittest_creature.get_weighted_fitness())?creature:fittest_creature;
	}
	return fittest_creature;
}

void Adaboost_model::update_weights(Eco_creature creature){
	correct_count = 0;
	cout << "\tAlpha: " << creature.get_alpha() << endl;
	for(Data_sample& sample:train_data.data_samples)
		upvote_mispredicted_sample(creature,sample);
	cout << "\tCorrect: " << correct_count << " of " << train_data.data_samples.size() << " | " << (double)correct_count/(double)train_data.data_samples.size() << endl;
	normalize_weights();
}

void Adaboost_model::upvote_mispredicted_sample(Eco_creature creature, Data_sample& sample){
	int prediction = creature.predict(sample.image);
	if(prediction != sample.label)
		sample.weight *= exp(creature.get_alpha());
	else
		correct_count++;
}

void Adaboost_model::normalize_weights(){
	double total = 0;
	for(Data_sample sample:train_data.data_samples)
		total+=sample.weight;
	for(Data_sample& sample:train_data.data_samples)
		sample.weight /= total;
}

bool Adaboost_model::is_creature_in_model(Eco_creature creature){
	for(auto model_creature:model_creatures){
		if(creature.get_genome() == model_creature.get_genome())
			return true;
	}
	return false;
}

void Adaboost_model::write(){
	string out_filename = results_path + "/adaboost_model";
	ofstream out_file(out_filename);
	for(Eco_creature creature:model_creatures){
		out_file << creature.get_alpha() << " " << creature.get_genome() << endl;
		creature.write_forest(results_path);
	}
	out_file.close();
}

void Adaboost_model::load(){
	string in_filename = results_path + "/adaboost_model";
	ifstream in_file(in_filename);
	assert(in_file);
	string line;
	while(getline(in_file,line)){
		load_creature(line,results_path);
	}
} 

void Adaboost_model::load_creature(string file_line,string path){
	istringstream ss(file_line);
	double alpha;
	string genome_string;
	ss >> alpha >> genome_string;
	model_creatures.push_back(Eco_creature(genome_string,alpha,path));
}

void Adaboost_model::test(){
	test_data.load_data();
	int num_correct = 0;
	for(Data_sample sample:test_data.data_samples){
		int prediction = get_weighted_prediction(sample.image);
		if(prediction == sample.label)
			num_correct++;
	}
	cout << "Percent correct: " << (double)num_correct/(double)test_data.data_samples.size() << endl;
}

int Adaboost_model::get_weighted_prediction(Mat image){
	vector<double> scores(MAX_NUM_CLASSES,0);
	for(Eco_creature creature:model_creatures){
		int prediction = creature.predict(image);
		scores.at(prediction) += creature.get_alpha();
	}
	double max_score = -1;
	int label = -1;
	for(unsigned int i = 0; i < scores.size(); i++){
		if(scores.at(i) > max_score){
			max_score = scores.at(i);
			label = i;
		}
	}
	return label;
}

int Adaboost_model::predict(string image_path){
	Mat image = imread(image_path,IMREAD_GRAYSCALE);
	image.convertTo(image,CV_32F);
	clock_t begin = clock();
	int prediction = get_weighted_prediction(image);
	clock_t end = clock();
	cout << "\tIn predict: " << end - begin << endl;
	return prediction;
}

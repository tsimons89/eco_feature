#pragma once

#include <opencv2/opencv.hpp>
#include "Data_set.hpp"
#include "Eco_population.hpp"

using namespace std;
using namespace cv;

#define MAX_NUM_CLASSES 100

class Adaboost_model{
private:
	vector<Eco_creature> model_creatures,pool_creatures;
	Data_set train_data,resample_data,test_data;
	int correct_count;
	void add_creature_to_model();
	void add_creature_to_pool();
	void set_resampled_data();
	void check_params();
	void update_model();
	Eco_creature select_from_pool();
	void update_weights(Eco_creature creature);
	void upvote_mispredicted_sample(Eco_creature creature,Data_sample& sample);
	void normalize_weights();
	bool is_creature_in_model(Eco_creature creature);
	void load_creature(string file_line,string path);
	int get_weighted_prediction(Mat image);

	static unsigned int num_creatures,pool_size;
	static string results_path;
public:
	Adaboost_model(){}
	void train();
	void write();
	void load();
	void test();
	int predict(string image_path);

	static void set_num_creatures(unsigned int num){num_creatures = num;}
	static void set_pool_size(unsigned int size){pool_size = size;}
	static void set_results_path(string path){results_path = path;}
};
#pragma once

#include <opencv2/opencv.hpp>
#include "Data_set.hpp"
#include "Population.hpp"

using namespace std;
using namespace cv;

#define MAX_NUM_CLASSES 100

class Adaboost_model{
private:
	vector<Creature> model_creatures,pool_creatures;
	Data_set train_data,resample_data,test_data;
	int correct_count;
	void add_creature_to_model();
	void add_creature_to_pool();
	void set_resampled_data();
	void check_params();
	void update_model();
	Creature select_from_pool();
	void update_weights(Creature creature);
	void upvote_mispredicted_sample(Creature creature,Data_sample& sample);
	void normalize_weights();
	bool is_creature_in_model(Creature creature);
	void load_creature(string file_line,string path);
	void format_image(Mat& image);

	static unsigned int num_creatures,pool_size;
	static string results_path;
public:
	Adaboost_model(){}
	void train();
	void write();
	void load();
	void test();
	int predict(string image_path);
	int predict(Mat image);

	static void set_num_creatures(unsigned int num){num_creatures = num;}
	static void set_pool_size(unsigned int size){pool_size = size;}
	static void set_results_path(string path){results_path = path;}
};
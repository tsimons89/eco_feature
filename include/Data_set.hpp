#pragma once
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include "probability.hpp"

#define WEIGHT_NOT_SET -1
#define SELECTION_POOL_SIZE 4

using namespace std;
using namespace cv;

typedef struct Data_sample{
	Mat image;
	int label;
	double weight;
} Data_sample;

class Data_set{
private:
	string path;
	vector<string> class_directories;
	int cur_label;
	int num_labels;
	void set_class_directories();
	void set_data_from_class_directories();
	void add_class_data();
	vector<String> get_all_filenames(string dir);
	void init_weights();
	void add_class_data(string dir);
	Mat get_image(string filename);
	Data_sample select_sample();
	Data_sample get_random_sample();

	static string data_set_path;
public:
	Data_set(){};
	void load_data();
	void set_samples(vector<Data_sample> samples){data_samples = samples;}
	void random_split(Data_set& set_1,Data_set& set_2, double percent_in_set_1);
	Data_set resample();
	vector<int> get_labels();
	vector<Mat> get_images();
	vector<double> get_weights();
	int get_num_labels(){return class_directories.size();}
	vector<Data_sample> data_samples;

	static void set_data_set_path(string path){data_set_path = path;}
};
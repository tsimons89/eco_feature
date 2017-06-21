#pragma once
#include <opencv2/opencv.hpp>
#include "Tree.hpp"
using namespace cv;
#define NOT_INIT -1

class Random_forest{
private:
	int num_trees = NOT_INIT;
	vector<Tree> trees;
	vector<int> get_random_indices(int num_samples);

public:
	Random_forest(){}
	Random_forest(string filename){}
	void set_params(int num_trees = 15,int max_depth = 10,int num_active_vars = 0,int min_indices = 2);
	void train(cv::Mat data, cv::Mat labels);
	void predict(cv::Mat data, cv::Mat& results);
	void write(string filename);
};
#pragma once
#include <opencv2/opencv.hpp>
#include "Tree_node.hpp"

class Tree{
private:

	Tree_node root;
	void init(cv::Mat data,cv::Mat labels);
	void init_root(int num_samples);

public:
	Tree(cv::Mat data, cv::Mat labels,vector<int> indices);
	Tree(string filename);
	static void set_params(int max_depth = 10,int num_active_vars = 0,int min_indices = 2);
	cv::Mat predict(cv::Mat data);
	void write(string filename);
};
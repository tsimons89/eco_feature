#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Eco_filter {
protected:
	bool is_yaml_file(string filename);
	Mat get_mat_from_yaml(string filename);
public:
	Eco_filter(){}
	virtual void load_from_file(string filename) = 0;
	virtual void apply_filter(Eco_filter& filter) = 0;


};
#pragma once

#include <opencv2/opencv.hpp>
#include "Eco_genome.hpp"
using namespace std;
using namespace cv;

class Eco_filter {
private:
	Mat image;
	Eco_genome genome;
	Mat apply(Mat image);
	void blur_x();
	void blur_y();
	void diff_x();
	void diff_y();

	void blur_x(int n);
	void blur_y(int n);
	void diff_x(int n);
	void diff_y(int n);



public:
	Eco_filter(Eco_genome genome): 
		genome(genome){}

	Mat apply(const vector<Mat>& images);
};



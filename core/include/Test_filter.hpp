#pragma once

#include <opencv2/opencv.hpp>
#include "Genome.hpp"
using namespace std;
using namespace cv;

class Test_filter {
private:
  Mat image,xb_image,yb_image,xd_image,yd_image;
	Genome genome;

	void blur_x();
	void blur_y();
	void diff_x();
	void diff_y();

	void blur_x(int n);
	void blur_y(int n);
	void diff_x(int n);
	void diff_y(int n);

public:
	Test_filter(Genome genome): 
		genome(genome){}
	Mat apply(Mat image);
	Mat apply(const vector<Mat>& images);
};

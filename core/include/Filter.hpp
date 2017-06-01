#pragma once

#include <opencv2/opencv.hpp>
#include "Genome.hpp"
#include <opencv2/core/cuda.hpp>
using namespace std;
using namespace cv;

class Filter {
private:
	Mat image;
	cuda::GpuMat gpu_image;
	Genome genome;
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
	Filter(Genome genome): 
		genome(genome){}
	Mat apply(const vector<Mat>& images);
};



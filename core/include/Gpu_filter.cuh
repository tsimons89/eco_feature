#pragma once

#include <opencv2/opencv.hpp>
#include "Genome.hpp"
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>

using namespace std;
using namespace cv;

#define THREAD_DIM 32

class Gpu_filter {
private:
	static Size size;
	static float* gpu_src,*gpu_dst;
	float* gpu_image;
	static bool initilized;
	bool first;

	Genome genome;
	Mat download();

	static void init(Size s);

	void filter(bool y_dir, bool subtract);

	void blur_x();
	void blur_y();
	void diff_x();
	void diff_y();

	void blur_x(int n);
	void blur_y(int n);
	void diff_x(int n);
	void diff_y(int n);

public:
	Gpu_filter(Genome genome) :genome(genome){}
	Mat apply(const vector<float*> gpu_images);
	Mat apply(float* gpu_image);

	static float* upload(Mat image);

};



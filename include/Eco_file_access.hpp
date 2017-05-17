#pragma once

#include <opencv2/opencv.hpp>
#include "Eco_filter.hpp"

using namespace std;
using namespace cv;
class Eco_file_access{
public:
	static vector<Eco_filter> get_filters_from_file(string filename);
	static Mat get_image(string filename);
	static cuda::GpuMat get_gpu_image(string filename);

};

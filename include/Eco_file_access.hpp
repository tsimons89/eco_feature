#pragma once

#include <opencv2/opencv.hpp>
#include "Eco_filter.hpp"

using namespace std;
using namespace cv;
class Eco_file_access{
private:
	static vector<String> get_all_filenames(string dir_path);
public:
	static vector<Eco_filter> get_filters_from_file(string filename);
	static Mat get_image(string filename);
	static cuda::GpuMat get_gpu_image(string filename);
	static vector<Mat> get_images(string dir_path);
	static vector<cuda::GpuMat> get_gpu_images(string dir_path);


};

#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Eco_filter {
private:
	Mat filter_mat;

	void extend_to_fit(const Size& other_filter_size);
public:
	Eco_filter();
	Eco_filter(Mat mat){filter_mat = mat;}
	Size get_size() const {return filter_mat.size();};
	Mat get_mat() const {return filter_mat;}
	Mat get_mat_rotated () const;

	void apply(const Eco_filter& filter);
	Mat apply(const Mat& image);
	cuda::GpuMat apply(const cuda::GpuMat& image);
};

std::ostream &operator<<(std::ostream &os, Eco_filter const &filter);

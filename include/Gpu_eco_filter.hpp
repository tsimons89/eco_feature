#pragma once

#include "Eco_filter.hpp"
#include "opencv2/core/cuda.hpp"

using namespace cv;
class Gpu_eco_filter : public virtual Eco_filter{
private:
	void upload_from_cv_mat();
	void download_to_cv_mat();
	Mat cv_mat;
	void extend_to_fit(const Size& other_filter_size);
	void rotate();
	void crop_extra(const Size& other_filter_size);
	void apply_filter(const Eco_filter& filter);
	cuda::GpuMat filter_mat;


public:
	Gpu_eco_filter(string filename){load_from_file(filename);}
	Gpu_eco_filter(Mat mat);
	Size get_size() const {return filter_mat.size();}
	void load_from_file(string filename);
	Mat get_cv_mat();
	cuda::GpuMat get_mat() const {return filter_mat;}
};

std::ostream &operator<<(std::ostream &os, Gpu_eco_filter &filter);
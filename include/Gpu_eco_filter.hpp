#pragma once

#include "Eco_filter.hpp"
#include "opencv2/core/cuda.hpp"

using namespace cv;
class Gpu_eco_filter : public virtual Eco_filter{
private:
public:
	cuda::GpuMat filter_mat;
	Mat cv_mat;
	Gpu_eco_filter(string filename){load_from_file(filename);}
	void load_from_file(string filename);
	void apply_filter(Eco_filter& filter);	
	cuda::GpuMat get_filter(){return filter_mat;}
	void download_to_cv_mat();
};

std::ostream &operator<<(std::ostream &os, Gpu_eco_filter &filter);
#pragma once

#include "Eco_filter.hpp"

using namespace cv;

class Cpu_eco_filter : public virtual Eco_filter{
private:
	Mat filter_mat;
	void extend_to_fit(const Size& other_filter_size);
	void rotate();
	void crop_extra(const Size& other_filter_size);
	void apply_filter(const Eco_filter& filter);
public:
	Cpu_eco_filter();
	Cpu_eco_filter(string filename){load_from_file(filename);}
	Cpu_eco_filter(Mat mat){filter_mat = mat;}
	Size get_size() const {return filter_mat.size();}
	void load_from_file(string filename);
	Mat get_mat() const {return filter_mat;}
};

std::ostream &operator<<(std::ostream &os, Cpu_eco_filter const &filter);

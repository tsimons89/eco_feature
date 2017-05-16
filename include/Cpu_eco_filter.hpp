#pragma once

#include "Eco_filter.hpp"

using namespace cv;

class Cpu_eco_filter : public virtual Eco_filter{
private:
public:
	Mat filter_mat;
	Cpu_eco_filter(string filename){load_from_file(filename);}
	Cpu_eco_filter(float * data,int rows, int cols);
	void load_from_file(string filename);
	void apply_filter(Eco_filter& filter);
	Mat get_mat() const {return filter_mat;}
};

std::ostream &operator<<(std::ostream &os, Cpu_eco_filter const &filter);

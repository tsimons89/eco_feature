#include "Cpu_eco_filter.hpp"
#include <iostream>

Cpu_eco_filter::Cpu_eco_filter(float * data,int rows, int cols){
	filter_mat = Mat(rows,cols,CV_32F,data);
}

void Cpu_eco_filter::load_from_file(string filename){
	filter_mat = imread(filename,IMREAD_GRAYSCALE);
	assert(filter_mat.total() > 0);
}

void Cpu_eco_filter::apply_filter(Eco_filter& filter){

}



std::ostream &operator<<(std::ostream &os, Cpu_eco_filter const &filter) { 
    return os << filter.get_mat();
}

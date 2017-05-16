#include "Gpu_eco_filter.hpp"

void Gpu_eco_filter::load_from_file(string filename){
	cv_mat = imread(filename,IMREAD_GRAYSCALE);
	assert(cv_mat.total() > 0);
	filter_mat.upload(cv_mat);
}
void Gpu_eco_filter::apply_filter(Eco_filter& filter){
}

void Gpu_eco_filter::download_to_cv_mat(){
	filter_mat.download(cv_mat);
}

std::ostream &operator<<(std::ostream &os, Gpu_eco_filter &filter) {
	//filter.download_to_cv_mat();
    return os << filter.cv_mat;
}

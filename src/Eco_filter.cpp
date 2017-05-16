#include "Eco_filter.hpp"

bool Eco_filter::is_yaml_file(string filename){
	return filename.find(".yaml") != string::nopos;
}

Mat Eco_filter::get_mat_from_yaml(string filename){
	
}
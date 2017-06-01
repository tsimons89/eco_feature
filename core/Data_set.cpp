#include "Data_set.hpp"

string Data_set::data_set_path;

void Data_set::random_split(Data_set& set_1,Data_set& set_2, double percent_in_set_1){
	int set_1_size = data_samples.size()*percent_in_set_1;
	vector<Data_sample> samples_1(set_1_size),samples_2(data_samples.size()-set_1_size);
	random_shuffle(data_samples.begin(),data_samples.end());
	copy(data_samples.begin(), data_samples.begin()+set_1_size,samples_1.begin());
	copy(data_samples.begin()+set_1_size,data_samples.end(),samples_2.begin());
	set_1.set_samples(samples_1);
	set_2.set_samples(samples_2);
}

void Data_set::load(string data_path){
	set_data_set_path(data_path);
	load();
}

void Data_set::load(){
	set_class_directories();
	set_data_from_class_directories();
	init_weights();
}

void Data_set::set_class_directories(){
	class_directories.clear();
	DIR * top_dir = opendir(data_set_path.c_str());
	struct dirent *entry = readdir(top_dir);
	while(entry != NULL){
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.')
                    class_directories.push_back(data_set_path +'/'+ entry->d_name);
   		entry = readdir(top_dir);
	}
}

void Data_set::set_data_from_class_directories(){
	data_samples.clear();
	cur_label = 0;
	for(string dir:class_directories)
		add_class_data(dir);
}

void Data_set::add_class_data(string dir){
	for(String filename:get_all_filenames(dir)){
		Data_sample new_sample = {.image = get_image(filename),.label = cur_label, .weight = WEIGHT_NOT_SET};
		data_samples.push_back(new_sample);
	}
	cur_label++;
}

vector<String> Data_set::get_all_filenames(string dir){
	vector<String> filenames;
	glob(String(dir),filenames);
	return filenames;
}

Mat Data_set::get_image(string filename){
	Mat image = imread(filename,IMREAD_GRAYSCALE);
	image.convertTo(image,CV_32F);
	return image;
}

void Data_set::init_weights(){
	for(Data_sample sample:data_samples)
		sample.weight = (double)1.0/data_samples.size();
}

vector<int> Data_set::get_labels(){
	vector<int> labels;
	for(Data_sample sample:data_samples)
		labels.push_back(sample.label);

	return labels;
}

vector<Mat> Data_set::get_images(){
	vector<Mat> images;
	for(Data_sample sample:data_samples){
		images.push_back(sample.image);
	}
	return images;
}

vector<double> Data_set::get_weights(){
	vector<double> weights;
	for(Data_sample sample:data_samples)
		weights.push_back(sample.weight);
	return weights;
}

Data_set Data_set::resample(){
	Data_set new_set;
	while(new_set.data_samples.size() < data_samples.size())
		new_set.data_samples.push_back(select_sample());
	return new_set;
}

Data_sample Data_set::select_sample(){
	Data_sample selected_sample = get_random_sample();
	for(int i = 0; i < SELECTION_POOL_SIZE-1; i++){
		Data_sample random_sample = get_random_sample();
		selected_sample = (selected_sample.weight>random_sample.weight)?selected_sample:random_sample;
	}
	return selected_sample;
}

Data_sample Data_set::get_random_sample(){
	int random_index = get_random_uint(data_samples.size()-1);
	return data_samples.at(random_index);
}






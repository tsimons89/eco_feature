#include "Eco_file_access.hpp"

vector<Eco_filter> Eco_file_access::get_filters_from_file(string filename){
	vector<Eco_filter> return_filters;
	FileStorage read(filename,FileStorage::READ);
	FileNode node = read["filters"];
	for (FileNodeIterator it=node.begin(); it!=node.end(); ++it)
	{
	    Mat mat;
	    (*it) >> mat;
	    return_filters.push_back(Eco_filter(mat));
	}
	read.release();
	return return_filters;
}

Mat Eco_file_access::get_image(string filename){
	Mat image = imread(filename,IMREAD_GRAYSCALE);
	image.convertTo(image,CV_32F);
	return image;
}

cuda::GpuMat Eco_file_access::get_gpu_image(string filename){
	Mat image = Eco_file_access::get_image(filename);
	cuda::GpuMat gpu_image;
	gpu_image.upload(image);
	return gpu_image;
}

vector<Mat> Eco_file_access::get_images(string dir_path){
	vector<Mat> images;
	for(auto filename:get_all_filenames(dir_path))
		images.push_back(get_image(filename));
	return images;

}
vector<cuda::GpuMat> Eco_file_access::get_gpu_images(string dir_path){
	vector<cuda::GpuMat> images;
	for(auto filename:get_all_filenames(dir_path))
		images.push_back(get_gpu_image(filename));
	return images;
}

vector<String> Eco_file_access::get_all_filenames(string dir_path){
	vector<String> filenames;
	glob(String(dir_path),filenames);
	return filenames;
}



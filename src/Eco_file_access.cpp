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


#include "Eco_filter.hpp"
#include <opencv2/cudaarithm.hpp>

Eco_filter::Eco_filter(){
	filter_mat = Mat::ones(1,1,CV_32F);
}

void Eco_filter::apply(const Eco_filter& filter){
	extend_to_fit(filter.get_size());
	filter2D(filter_mat,filter_mat,-1,filter.get_mat_rotated(),Point(-1,-1),0,BORDER_REPLICATE);
}

Mat Eco_filter::apply(const Mat& image){
	Mat ret_image;
	image.convertTo(ret_image,CV_32F);
	filter2D(ret_image,ret_image,-1,get_mat_rotated());
	return ret_image;
}

cuda::GpuMat Eco_filter::apply(const cuda::GpuMat& image){
	cuda::GpuMat ret_image;
	Ptr<cuda::Filter> cu_filter_ptr = cuda::createLinearFilter(filter_mat.type(),filter_mat.type(),get_mat_rotated());
	cu_filter_ptr->apply(image,ret_image);
	// Ptr<cuda::Convolution> conv = cuda::createConvolution();
	// conv->convolve(image,get_mat_rotated(),ret_image);
	return ret_image;
}

vector<Mat> Eco_filter::apply(const vector<Mat>& images){
	vector<Mat> ret_images;
	Mat merged,ret_merged;
	merge(images,merged);
	ret_merged = apply(merged);
	split(ret_merged,ret_images);
	return ret_images;
}

vector<Mat> Eco_filter::apply_loop(const vector<Mat>& images){
	vector<Mat> ret_images;
	for(Mat image:images){
		cout << "loop\n";
		ret_images.push_back(apply(image));
	}
	return ret_images;
}



vector<cuda::GpuMat> Eco_filter::apply(const vector<cuda::GpuMat>& images){
	vector<cuda::GpuMat> ret_images;
	Mat merged,ret_merged;
	cuda::merge(images,merged);
	ret_merged = apply(merged);
	cuda::split(ret_merged,ret_images);
	return ret_images;
}



void Eco_filter::extend_to_fit(const Size& other_filter_size){
	int top_bot_ext = other_filter_size.height/2;
	int r_l_ext = other_filter_size.width/2;
	copyMakeBorder(filter_mat,filter_mat,top_bot_ext,top_bot_ext,r_l_ext,r_l_ext,BORDER_CONSTANT,Scalar::all(0));
}
Mat Eco_filter::get_mat_rotated() const {
	Point2f center = Point2f(filter_mat.cols/2,filter_mat.rows/2);
	Mat ret_mat,rot_mat = getRotationMatrix2D(center,180,1);
	warpAffine(filter_mat,ret_mat,rot_mat,filter_mat.size());
	return ret_mat;
}

std::ostream &operator<<(std::ostream &os, Eco_filter const &filter) { 
    return os << filter.get_mat();
}

#include "Filter.hpp"

Mat Filter::apply(const vector<Mat>& images){
	Mat ret_images;
	for(Mat image:images)
		ret_images.push_back(apply(image));
	return ret_images;
}


Mat Filter::apply(Mat image){
	this->image = image;
	blur_x(genome.x_blur);
	blur_y(genome.y_blur);
	diff_x(genome.x_diff);
	diff_y(genome.y_diff);
	return this->image;	
}

void Filter::blur_x(){
	Size new_size(image.cols-1,image.rows);
	image = image(Rect(Point(1,0),new_size)) + image(Rect(Point(0,0),new_size));
	image /=2;
}

void Filter::blur_y(){
	Size new_size(image.cols,image.rows-1);
	image = image(Rect(Point(0,1),new_size)) + image(Rect(Point(0,0),new_size));
	image /=2;

}

void Filter::diff_x(){
	Size new_size(image.cols-1,image.rows);
	image = image(Rect(Point(1,0),new_size)) - image(Rect(Point(0,0),new_size));
	image /=2;
}

void Filter::diff_y(){
	Size new_size(image.cols,image.rows-1);
	image = image(Rect(Point(0,1),new_size)) - image(Rect(Point(0,0),new_size));
	image /=2;
}

void Filter::blur_x(int n){
	for(int i = 0; i < n; i++)
		blur_x();
}

void Filter::blur_y(int n){
	for(int i = 0; i < n; i++)
		blur_y();
}

void Filter::diff_x(int n){
	for(int i = 0; i < n; i++)
		diff_x();
}

void Filter::diff_y(int n){
	for(int i = 0; i < n; i++)
		diff_y();
}




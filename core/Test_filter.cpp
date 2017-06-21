#include "Test_filter.hpp"

bool checker = true;
Mat Test_filter::apply(const vector<Mat>& images){
	Mat ret_images;
	for(Mat image:images)
		ret_images.push_back(apply(image));
	return ret_images;
}


Mat Test_filter::apply(Mat image){
  if(checker){
    cout << "Test filter !\n";
    checker = false;
  }
	this->image = image;
	blur_x(genome.x_blur);
	blur_y(genome.y_blur);
	diff_x(genome.x_diff);
	diff_y(genome.y_diff);

	int min_rows = min(xb_image.rows,yb_image.rows);
	min_rows = min(min_rows,xd_image.rows);
	min_rows = min(min_rows,yd_image.rows);
     
	int min_cols = min(xb_image.cols,yb_image.cols);
	min_cols = min(min_cols,xd_image.cols);
	min_cols = min(min_cols,yd_image.cols);

	Size small_size(min_cols,min_rows);
	Rect small_rect(Point(0,0),small_size);
	xb_image = xb_image(small_rect);
	yb_image = yb_image(small_rect);
	xd_image = xd_image(small_rect);
	yd_image = yd_image(small_rect);
	
	
	return (xb_image + yb_image + xd_image + yd_image)/4;	
}

void Test_filter::blur_x(){
	Size new_size(xb_image.cols-1,xb_image.rows);
	xb_image = xb_image(Rect(Point(1,0),new_size)) + xb_image(Rect(Point(0,0),new_size));
	xb_image /=2;
}

void Test_filter::blur_y(){
	Size new_size(yb_image.cols,yb_image.rows-1);
	yb_image = yb_image(Rect(Point(0,1),new_size)) + yb_image(Rect(Point(0,0),new_size));
	yb_image /=2;

}

void Test_filter::diff_x(){
	Size new_size(xd_image.cols-1,xd_image.rows);
	xd_image = xd_image(Rect(Point(1,0),new_size)) - xd_image(Rect(Point(0,0),new_size));
	xd_image /=2;
}

void Test_filter::diff_y(){
	Size new_size(yd_image.cols,yd_image.rows-1);
	yd_image = yd_image(Rect(Point(0,1),new_size)) - yd_image(Rect(Point(0,0),new_size));
	yd_image /=2;
}

void Test_filter::blur_x(int n){
  xb_image = image.clone();
  for(int i = 0; i < n; i++)
		blur_x();
}

void Test_filter::blur_y(int n){
  yb_image = image.clone();
  for(int i = 0; i < n; i++)
		blur_y();
}

void Test_filter::diff_x(int n){
  xd_image = image.clone();
  for(int i = 0; i < n; i++)
		diff_x();
}

void Test_filter::diff_y(int n){
  yd_image = image.clone();
  for(int i = 0; i < n; i++)
		diff_y();
}

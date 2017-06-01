#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define THRESH 100

class Component_finder{

private:
	void process_image_for_segmentation();
	void set_components_stats();
	void remove_background_stats();
	int largest_label;
	double largest_area;
	Mat stats,centers;
	Mat image;

public:
	Component_finder(){}
	Component_finder(Mat image){set_image(image);}
	void set_image(Mat image);
	Mat get_image(){return image;}
	Point get_largest_component_center();
	double get_largest_component_area(){return largest_area;}
	void set_largest_component();
};

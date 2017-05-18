#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include "Eco_filter.hpp"
#include "Eco_file_access.hpp"
#include <ctime>

using namespace std;

#define CALC_TIME(F,s) clock_t begin##s = clock();F; clock_t end##s = clock();cout << "Cycles " << s << ": " << end##s - begin##s << endl;

int main(int argc, char * argv[]){
	vector<Eco_filter> filters = Eco_file_access::get_filters_from_file("test.yaml");
	Eco_filter sobel = filters.at(1);

	vector<Mat> images = Eco_file_access::get_images(argv[1]);

	CALC_TIME(vector<Mat> images_applied = sobel.apply(images),1)
	CALC_TIME(vector<Mat> images_loop = sobel.apply_loop(images),2)
	CALC_TIME(vector<Mat> images_applied_2 = sobel.apply(images),3)
	CALC_TIME(vector<Mat> images_loop_2 = sobel.apply_loop(images),4)


}
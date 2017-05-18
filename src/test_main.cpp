#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include "Eco_filter.hpp"
#include "Eco_file_access.hpp"
#include <ctime>

using namespace std;

#define CALC_TIME(F,s) clock_t begin##s = clock();F; clock_t end##s = clock();cout << "Cycles " << s << ": " << end##s - begin##s << endl;
void my_cv_filter(Mat m){
	Sobel(m,m,-1,1,0);
	Sobel(m,m,-1,1,0);
	Sobel(m,m,-1,1,0);
	Sobel(m,m,-1,1,0);
}

void my_filter(Mat m,Eco_filter& filter){
	filter.apply(m);
}


int main(int argc, char * argv[]){
	vector<Eco_filter> filters = Eco_file_access::get_filters_from_file("test.yaml");
	Eco_filter sobel = filters.at(1);
	Eco_filter filter;
	filter.apply(sobel);
	filter.apply(sobel);
	filter.apply(sobel);
	filter.apply(sobel);
	cout << "Filter: " << filter << endl;
	Mat image = Eco_file_access::get_image(argv[1]);

	my_filter(image,sobel);
	my_cv_filter(image);
	CALC_TIME(my_filter(image,sobel),1)
	CALC_TIME(my_cv_filter(image),2)



}

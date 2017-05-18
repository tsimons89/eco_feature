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

	Mat image = Eco_file_access::get_image(argv[1]);
	cuda::GpuMat gpu_image = Eco_file_access::get_gpu_image(argv[1]);
	CALC_TIME(sobel.apply(image),1)
	CALC_TIME(sobel.apply(image),2)
	CALC_TIME(sobel.apply(gpu_image),3)
	CALC_TIME(sobel.apply(gpu_image),4)
	CALC_TIME(Sobel(image,image,-1,1,0),5)
	CALC_TIME(Sobel(image,image,-1,0,1),6)

}
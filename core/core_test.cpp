#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include "Gpu_filter.cuh"
#include "Filter.hpp"
#include "Genome.hpp"
#include <ctime>

using namespace std;
using namespace cv;

int main(int argc, char * argv[]){
	assert(argc >= 2);
	Mat image = imread(argv[1],IMREAD_GRAYSCALE);
	image.convertTo(image,CV_32F);

	Genome g(3,3,0,0);
	Gpu_filter gpu_filter(g);
	Filter cpu_filter(g);

	float* gpu_image = Gpu_filter::upload(image);
	Mat res = gpu_filter.apply(gpu_image);


	clock_t begin = clock();
	res = gpu_filter.apply(gpu_image);
	clock_t end = clock();

	cout << "Clocks: " << end - begin << endl;


	Mat r = cpu_filter.apply(image);


	begin = clock();
	r = cpu_filter.apply(image);
	end = clock();
	cout << "CPU clocks: " << end - begin << endl;


	Mat diff;
	absdiff(r,res,diff);
	res.convertTo(res,CV_8U);
	r.convertTo(r,CV_8U);
	imshow("result",res);
	imshow("cpu", r);
	imshow("diff",diff);
	waitKey(0);
}

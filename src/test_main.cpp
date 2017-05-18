#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include "Eco_filter.hpp"
#include "Eco_file_access.hpp"
#include <ctime>

using namespace std;

int main(int argc, char * argv[]){
	vector<Eco_filter> filters = Eco_file_access::get_filters_from_file("test.yaml");

	Eco_filter orig;

	Eco_filter box = filters.at(0);
	Eco_filter sobel = filters.at(1);
	Eco_filter der = filters.at(2);
	orig.apply(sobel);
	orig.apply(box);
	orig.apply(sobel);
	orig.apply(box);


	cuda::GpuMat image_gpu = Eco_file_access::get_gpu_image(argv[1]);

	clock_t begin, end;

	begin = clock();
	cuda::GpuMat combo_gpu = orig.apply(image_gpu);
	end = clock();
	cout << "Combo time: " << end - begin << endl;

	begin = clock();
	combo_gpu = orig.apply(image_gpu);
	end = clock();
	cout << "Combo time: " << end - begin << endl;


	begin = clock();
	cuda::GpuMat multi_gpu = box.apply(sobel.apply(box.apply(sobel.apply(image_gpu))));
	end = clock();
	cout << "Multi time: " << end - begin << endl;

	begin = clock();
	multi_gpu = box.apply(sobel.apply(box.apply(sobel.apply(image_gpu))));
	end = clock();
	cout << "Multi time: " << end - begin << endl;

	Mat image = Eco_file_access::get_image(argv[1]);

	begin = clock();
	Mat combo_cpu = orig.apply(image);
	end = clock();
	cout << "Cpu combo time: " << end - begin << endl;



	begin = clock();
	Mat multi_image = box.apply(sobel.apply(box.apply(sobel.apply(image))));
	end = clock();
	cout << "Cpu multi time: " << end - begin << endl;

	Mat cpu_test = image;

	begin = clock();
	Sobel(cpu_test,cpu_test,-1,1,0);
	boxFilter(cpu_test,cpu_test,-1,Size(5,5),Point(-1,-1),false);
	Sobel(cpu_test,cpu_test,-1,1,0);
	boxFilter(cpu_test,cpu_test,-1,Size(5,5),Point(-1,-1),false);
	end = clock();
	cout << "Cpu cv time: " << end - begin << endl;

	cuda::GpuMat gpu_test = image_gpu; 
	gpu_test.convertTo(gpu_test,CV_8UC1);
	Ptr<cuda::Filter> box_filter = cuda::createBoxFilter(gpu_test.type(),gpu_test.type(),Size(5,5));
	Ptr<cuda::Filter> sobel_filter = cuda::createSobelFilter(gpu_test.type(),gpu_test.type(),1,0);

	begin = clock();
	sobel_filter->apply(gpu_test,gpu_test);	
	box_filter->apply(gpu_test,gpu_test);
	sobel_filter->apply(gpu_test,gpu_test);	
	box_filter->apply(gpu_test,gpu_test);
	end = clock();
	cout << "Gpu cv time: " << end - begin << endl;


	waitKey(0);
}

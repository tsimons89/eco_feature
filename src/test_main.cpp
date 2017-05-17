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
	orig.apply(der);
	orig.apply(box);
	orig.apply(der);
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
	cuda::GpuMat multi_gpu = box.apply(der.apply(box.apply(der.apply(image_gpu))));
	end = clock();
	cout << "Multi time: " << end - begin << endl;

	Mat image = Eco_file_access::get_image(argv[1]);
	begin = clock();
	Mat multi_image = box.apply(der.apply(box.apply(der.apply(image))));
	end = clock();
	cout << "Cpu time: " << end - begin << endl;





	waitKey(0);
}
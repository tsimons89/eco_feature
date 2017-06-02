#include <opencv2/opencv.hpp>
#include "Eco_options.hpp"
#include "Adaboost_model.hpp"
#include <ctime>

using namespace std;
using namespace cv;

int main(int argc, char * argv[]){
	Eco_options options;
	options.parse_single_predict_options(argc,argv);
	Adaboost_model tester;
	tester.load();

	clock_t begin,end;
	int prediction;
	double min_clocks = 100000000;
	double max_clocks = 0;
	for(int i = 0; i < 10; i++){
		begin = clock();
		prediction = tester.predict(options.get_image_path());
		end = clock();
		double clocks = end - begin;
		min_clocks = min(min_clocks,clocks);
		max_clocks = max(max_clocks,clocks);
	}


	cout << "Max Time: " << max_clocks/(double)CLOCKS_PER_SEC * 1000.0 << " ms\n";
	cout << "Min Time: " << min_clocks/(double)CLOCKS_PER_SEC * 1000.0 << " ms\n";
	cout << "Prediction: " << prediction << endl;
}

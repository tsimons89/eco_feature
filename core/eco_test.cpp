#include <opencv2/opencv.hpp>
#include "Eco_options.hpp"
#include "Adaboost_model.hpp"

using namespace std;
using namespace cv;

int main(int argc, char * argv[]){
	Eco_options options;
	options.parse_test_options(argc,argv);
	Adaboost_model tester;
	tester.load();
	tester.test();
}

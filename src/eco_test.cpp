#include <opencv2/opencv.hpp>
#include "Options.hpp"
#include "Adaboost_model.hpp"

using namespace std;
using namespace cv;

int main(int argc, char * argv[]){
	Options options;
	options.parse_test_options(argc,argv);
	Adaboost_model tester;
	tester.load();
	tester.test();
}

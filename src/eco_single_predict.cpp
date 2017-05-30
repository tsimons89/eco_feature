#include <opencv2/opencv.hpp>
#include "Options.hpp"
#include "Adaboost_model.hpp"
#include <ctime>

using namespace std;
using namespace cv;

int main(int argc, char * argv[]){
	Options options;
	options.parse_single_predict_options(argc,argv);
	Adaboost_model tester;
	tester.load();

	clock_t begin = clock();
	int prediction = tester.predict(options.get_image_path());
	clock_t end = clock();
	cout << "Time: " << end-begin << endl;

	begin = clock();
	prediction = tester.predict(options.get_image_path());
	end = clock();
	cout << "Time: " << end-begin << endl;

	 cout << "Prediction: " << prediction << endl;
}

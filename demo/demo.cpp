#include "Demo_options.h"
#include "Camera_capture.h"
#include "Adaboost_model.hpp"

using namespace std;
using namespace cv;

int main(int argc, char * argv[]){
	Demo_options options;
	options.parse_options(argc,argv);
	Adaboost_model tester;
	tester.load();
	Camera_capture * cap_ptr = options.get_camera_cap_ptr();

	while(1){
		Mat image = cap_ptr->get_next_object();
		int prediction = tester.predict(image);
		cout << "Prediction: " << prediction << endl;
	}
}

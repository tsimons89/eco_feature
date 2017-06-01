#include <opencv2/opencv.hpp>
#include "Eco_options.hpp"
#include "Adaboost_model.hpp"
#include "probability.hpp"

using namespace std;
using namespace cv;

int main(int argc, char * argv[]){
	Eco_options options;
	options.parse_train_options(argc,argv);
	init_rand();
	Adaboost_model trainer;
	trainer.train();
	trainer.write();
}

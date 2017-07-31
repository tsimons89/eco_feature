#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include "Genome.hpp"
#include "Filter.hpp"
#include <ctime>

using namespace std;
using namespace cv;
using namespace ml;


int main(int argc, char * argv[]){
  Ptr<RTrees> forest;

  forest = RTrees::load(argv[1]);
  
  Mat image = imread(argv[2],IMREAD_GRAYSCALE);
  image.convertTo(image,CV_32S);
  image *= 2;

  Genome g(1,1,0,0);
  Filter f(g);

  image = f.apply(image);
  
  
  Mat result;
  image.reshape(0,1);
  int var = atoi(argv[3]);
  cout << "Var " << var << ": " << image.at<int>(0,var) << endl;
  image.convertTo(image,CV_32F);
  forest->predict(image,result);
  float prediction = result.at<float>(0,0);
  cout << "Prediction: " << prediction  << endl;
}

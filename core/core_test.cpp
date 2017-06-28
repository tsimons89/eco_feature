#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include "Data_set.hpp"
#include "Gini.hpp"
#include <ctime>

using namespace std;
using namespace cv;
using namespace ml;


int main(int argc, char * argv[]){
  assert(argc == 2);
  Data_set data;
  data.load(argv[1]);
  Gini gini;
  gini.display_heat_map(data);
}

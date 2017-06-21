#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include "Filter.hpp"
#include "Filter_set.hpp"
#include <ctime>

using namespace std;
using namespace cv;
using namespace ml;

int my_print(int i){
  cout << "My num: " << i << endl;
  return 50;
}

int main(int argc, char * argv[]){
  // int index = 0;
  // int array[3] = {1,10,100};
  // array[++index] = my_print(index -1);
  // for(int i = 0;i<3;i++)
  //   cout << "Array: " << array[i] << endl;
  assert(argc == 2);
  Mat original = imread(argv[1],IMREAD_GRAYSCALE);
  original.convertTo(original,CV_32F);

  Filter_set::set_max(5,5,1,1);
  clock_t b = clock();
  Filter_set set(original);
  clock_t e = clock();
  cout << "set: " << e-b << endl;

  b = clock();
  Filter_set set2(original);
  e = clock();
  cout << "set2: " << e-b << endl;
  
  
  for(int xd = 0; xd <= 1; xd++){
    for(int yd = 0; yd <= 1; yd++){
      for(int xb = 0; xb <= 5; xb++){
  	for(int yb = 0; yb <= 5; yb++){
  	  Genome g(xb,yb,xd,yd);
  	  Filter filter(g);
  	  Mat filter_image = filter.apply(original);
  	  Mat set_image = set.get_image(g);
  	  Mat diff;
  	  absdiff(filter_image,set_image,diff);
  	  diff.convertTo(diff,CV_8U);
  	  imshow("diff",diff*1000);
  	  waitKey(30);
  	}
      }
    }
  }
  
}

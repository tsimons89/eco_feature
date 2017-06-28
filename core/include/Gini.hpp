#include "Data_set.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Gini{
  Mat heat_map;
  vector<Mat> data;
  vector<int> labels;
  int max_label;
  vector<int> indices;
  void build_heat_map();
  float get_gini(int row,int col);
  vector<int> get_labels_hist();
public:
  Gini(){}
  void display_heat_map(Data_set data);
};

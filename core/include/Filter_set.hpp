#pragma once
#include <opencv2/opencv.hpp>
#include "Genome.hpp"

using namespace std;
using namespace cv;

class Filter_set{
private:
  Mat image;
  vector<vector<vector<vector<Mat>>>> images;
  Mat* image_array;
  vector<Mat> x_blur(Mat image);
  vector<vector<Mat>> x_y_blur(Mat image);
  vector<vector<vector<Mat>>> x_diff_blur(Mat image);
  void set_images();
  void new_set_images();
  Mat apply(Mat image, bool x_dir, bool blur);
  static int x_blur_max,y_blur_max,x_diff_max,y_diff_max;
public:
  Filter_set(Mat image);
  Mat get_image(Genome g);
  static void set_max(int x_blur,int y_blur,int x_diff,int y_diff);
};

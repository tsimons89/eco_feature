#include "Filter_set.hpp"

int Filter_set::x_blur_max,Filter_set::y_blur_max,Filter_set::x_diff_max,Filter_set::y_diff_max;

void Filter_set::set_max(int x_blur,int y_blur,int x_diff,int y_diff){
  x_blur_max = x_blur;
  y_blur_max = y_blur;
  x_diff_max = x_diff;
  y_diff_max = y_diff;
}


Filter_set::Filter_set(Mat image){
  this->image = image;
  new_set_images();
}

Mat Filter_set::get_image(Genome g){
  int index = g.x_blur + (x_blur_max+1)*(g.y_blur + (y_blur_max+1)*(g.x_diff + (x_diff_max+1)*g.y_diff));
  return image_array[index];
}

vector<Mat> Filter_set::x_blur(Mat image){
  vector<Mat> images;
  images.push_back(image);
  for(int i = 0; i < x_blur_max; i++)
    images.push_back(apply(images.back(),true,true));
  return images;
}

vector<vector<Mat>> Filter_set::x_y_blur(Mat image){
  vector<vector<Mat>> images;
  Mat cur_image = image.clone();
  images.push_back(x_blur(cur_image));
  for(int i = 0; i < y_blur_max; i++){
    cur_image = apply(cur_image,false,true);
    images.push_back(x_blur(cur_image));
  }
  return images;
}

vector<vector<vector<Mat>>> Filter_set::x_diff_blur(Mat image){
  vector<vector<vector<Mat>>> images;
  Mat cur_image = image.clone();
  images.push_back(x_y_blur(cur_image));
  for(int i = 0; i < x_diff_max; i++){
    cur_image = apply(cur_image,true,false);
    images.push_back(x_y_blur(cur_image));
  }
  return images;
}

void Filter_set::set_images(){
  images.clear();
  Mat cur_image = image.clone();
  images.push_back(x_diff_blur(cur_image));
  for(int i = 0; i < y_diff_max; i++){
    cur_image = apply(cur_image,false,false);
    images.push_back(x_diff_blur(cur_image));
  }
}
void Filter_set::new_set_images(){
  int num_images = (x_blur_max+1) * (y_blur_max+1) * (x_diff_max+1) * (y_diff_max+1);
  image_array = new Mat[num_images];
  int index = 0;
  image_array[index] = image.clone();
  for(int yd = 0; yd <= y_diff_max; yd++){
    if(yd > 0){
      Mat new_image = apply(image_array[++index-(x_blur_max+1) * (y_blur_max+1) * (x_diff_max+1)],false,false);
      image_array[index] = new_image;
    }
    for(int xd = 0; xd <= x_diff_max; xd++){
      if(xd > 0){
	Mat new_image = apply(image_array[++index-(x_blur_max +1)*(y_blur_max + 1)],true,false);
	image_array[index] = new_image;	
      }
      for(int yb = 0; yb <= y_blur_max; yb++){
	if(yb > 0){
	  Mat new_image = apply(image_array[++index-(x_blur_max+1)],false,true);
	  image_array[index] = new_image;
	}
	for(int xb = 0; xb < x_blur_max; xb++){
	  Mat new_image =  apply(image_array[index++],true,true);
	  image_array[index] = new_image;
	}
      }
    }
  }
}


Mat Filter_set::apply(Mat image,bool x_dir,bool blur){
  Size new_size(image.cols-1,image.rows);
  Point shifted_point;
  if(x_dir){
    shifted_point = Point(1,0);
    new_size = Size(image.cols-1,image.rows);
  }
  else{
    shifted_point = Point(0,1);
    new_size = Size(image.cols,image.rows-1);
  }
  Mat ret_image;
  if(blur)
    ret_image = image(Rect(shifted_point,new_size)) + image(Rect(Point(0,0),new_size));
  else
    ret_image = image(Rect(shifted_point,new_size)) - image(Rect(Point(0,0),new_size));
    
  ret_image /=2;
  return ret_image;
}

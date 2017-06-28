#include "Gini.hpp"

struct indexed_compare
{
  indexed_compare(const vector<Mat> images,int row,int col)
    : images(images), row(row),col(col) {}
  bool operator ()(int a, int b) const {
    return images[a].at<float>(row,col) < images[a].at<float>(row,col);
  }
  vector<Mat> images;
  int row,col;
};


void Gini::display_heat_map(Data_set data){
  this->data = data.get_images();
  this->labels = data.get_labels();
  heat_map = Mat::zeros(this->data[0].size(),this->data[0].type());
  indices.resize(this->data.size());
  max_label = *(max_element(labels.begin(),labels.end()));
  iota(indices.begin(),indices.end(),0);
  build_heat_map();
  normalize(heat_map,heat_map,255,0,NORM_MINMAX);
  Mat disp;
  heat_map.convertTo(disp,CV_8U);
  imshow("gini purity",heat_map);
  waitKey(0);
}

void Gini::build_heat_map(){
  for(int row = 0; row < data[0].rows; row++){
    cout << "row " << row << " of " << data[0].rows << endl;
    for(int col = 0; col < data[0].cols; col++)
      heat_map.at<float>(row,col) = get_gini(row,col);
  }
}

float Gini::get_gini(int row,int col){
  sort(indices.begin(),indices.end(),indexed_compare(data,row,col));
  vector<int> l_hist = vector<int>(max_label+1,0);
  vector<int> r_hist = get_labels_hist();
  double rsum,r2sum,lsum,l2sum;
  float value;
  int most_idx;
  vector<float> qualities;
  rsum = lsum = r2sum = l2sum = 0;
  for(int hist_el:r_hist){
    rsum+=hist_el;
    r2sum+=hist_el*hist_el;
  }
  float  gini_quality = -1;
  for(int idx:indices){
    if(idx == indices.back())
      break;
    rsum--;
    lsum++;
    r2sum-=r_hist[labels[idx]]*2-1;
    l2sum+=l_hist[labels[idx]]*2+1;
    r_hist[labels[idx]]--;
    l_hist[labels[idx]]++;
    double quality = (l2sum*rsum+r2sum*lsum)/(lsum*rsum);
    qualities.push_back(quality);
    if(quality > gini_quality){
      gini_quality = quality;
    }
  }
  return gini_quality;
}
vector<int> Gini::get_labels_hist(){
  vector<int> hist(max_label+1,0);
  vector<int>::iterator iter;
  for(int i = 0; i < hist.size(); i++)
    hist[i] = count(labels.begin(),labels.end(),i);
  return hist;
}

#include "Cpu_eco_filter.hpp"
#include "Gpu_eco_filter.hpp"

using namespace std;

int main(int argc, char * argv[]){
	// Cpu_eco_filter filter(argv[1]);
	// Gpu_eco_filter filter_gpu(argv[1]);
	// float data1 [3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	// float data2 [3][3] = {{1,1,1},{2,2,2},{3,3,3}};
	// float data3 [3][3] = {{9,8,7},{6,5,4},{3,2,1}};
	// float data4 [3][3] = {{0,0,0},{0,0,0},{0,0,0}};
	// vector<Mat> mat_vec;
	// mat_vec.push_back(Mat(Size(3,3),CV_32F,&data1));
	// mat_vec.push_back(Mat(Size(3,3),CV_32F,&data2));
	// mat_vec.push_back(Mat(Size(3,3),CV_32F,&data3));
	// mat_vec.push_back(Mat(Size(3,3),CV_32F,&data4));

	// FileStorage fs("test.yaml",FileStorage::WRITE);
	// fs << "filters" << mat_vec;
	// fs.release();

	vector<Mat> mat_vec_read;
	FileStorage read("test.yaml",FileStorage::READ);
	FileNode filters_node = read["filters"];
	for (FileNodeIterator it=filters_node.begin(); it!=filters_node.end(); ++it)
	{
	    Mat mat;
	    (*it) >> mat;
	    mat_vec_read.push_back(mat);
	}
	read.release();

	for(Mat mat : mat_vec_read){
		cout << mat.type() << endl;
		cout << mat << endl;
	}

}
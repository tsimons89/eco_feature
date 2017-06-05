#include "Gpu_filter.cuh"


dim3 blocks;
dim3 threads;
Size Gpu_filter::size;
float* Gpu_filter::gpu_src;
float* Gpu_filter::gpu_dst;
bool Gpu_filter::initilized = false;


__global__ void filter_kernel( float *in, float *out,bool y_dir, bool subtract, int cols,int rows) {
	int x = blockIdx.x * blockDim.x + threadIdx.x; 
	int y = blockIdx.y * blockDim.y + threadIdx.y;
	int pixel_index = y*cols +x;
	if(x >= cols || y >= rows){
		//out[pixel_index] = 0;
		return;
	}

	float pixel = in[pixel_index];

	float adj_pixel,res;
	if(y_dir)
		adj_pixel = in[pixel_index + cols];
	else
		adj_pixel = in[pixel_index + 1];

	if(subtract)
		res = adj_pixel - pixel;
	else
		res = adj_pixel + pixel;

	out[pixel_index] = res/2;
}

Mat Gpu_filter::apply(const vector<float*> gpu_images){
	Mat ret_images;
	for(int i = 0; i < gpu_images.size();i++)
		ret_images.push_back(apply(gpu_images.at(i)));
	return ret_images;
}

Mat Gpu_filter::apply(float* gpu_image){
	this->gpu_image = gpu_image;
	first = true;
	blur_x(genome.x_blur);
	blur_y(genome.y_blur);
	diff_x(genome.x_diff);
	diff_y(genome.y_diff);
	return download();	
}

float* Gpu_filter::upload(Mat image){
	if(!initilized)
		init(image.size());
	float* image_data = (float*)image.data;
	float* ret_image;
	cudaMalloc((void**)&ret_image, size.area() * sizeof(float));
	cudaMemcpy( ret_image, image_data, size.area() * sizeof(float),cudaMemcpyHostToDevice);
	return ret_image;
}

void Gpu_filter::init(Size s){
	size = s;
	cudaMalloc((void**)&gpu_src, size.area() * sizeof(float));
	cudaMalloc((void**)&gpu_dst, size.area() * sizeof(float));
	initilized = true;
	blocks = dim3((size.width + THREAD_DIM - 1)/THREAD_DIM ,(size.height + THREAD_DIM - 1)/THREAD_DIM);
	threads = dim3(THREAD_DIM,THREAD_DIM);
}

Mat Gpu_filter::download(){
	float* data = (float*)malloc(size.area()*sizeof(float));
	cudaMemcpy(data,gpu_src,size.area()*sizeof(float),cudaMemcpyDeviceToHost);
	Mat res_image(size,CV_32F,data);
	Size new_size(size.width - (genome.x_blur+genome.x_diff),size.height - (genome.y_blur + genome.y_diff));
	Rect roi(Point(0,0),new_size);
	Mat small_image(res_image,roi);
	return Mat(res_image,roi);
}

void Gpu_filter::filter(bool y_dir, bool subtract){
	if(first){
		first = false;
		filter_kernel<<<blocks,threads>>>(gpu_image,gpu_dst,y_dir,subtract,size.width,size.height);
	}
	else
		filter_kernel<<<blocks,threads>>>(gpu_src,gpu_dst,y_dir,subtract,size.width,size.height);
	float * tmp = gpu_src;
	gpu_src = gpu_dst;
	gpu_dst = tmp;
}

void Gpu_filter::blur_x(int n){
	for(int i = 0; i < n; i++)
		filter(false,false);
}

void Gpu_filter::blur_y(int n){
	for(int i = 0; i < n; i++)
		filter(true,false);
}

void Gpu_filter::diff_x(int n){
	for(int i = 0; i < n; i++)
		filter(false,true);
}

void Gpu_filter::diff_y(int n){
	for(int i = 0; i < n; i++)
		filter(true,true);
}




#pragma once

class Training_data_set {
private:
	vector<Training_image>
public:
	Training_data_set(string train_data_path);

};

class Training_image{
private:
	InputArrat
public:
	Training_image()
};

class Gpu_training_image : public Training_image{
public:
	Gpu_training_image(cuda::GpuMat image)
};
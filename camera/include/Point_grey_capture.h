#pragma once

#include <opencv2/opencv.hpp>
#include "FlyCapture2.h"
#include "Camera_capture.h"

using namespace std;
using namespace cv;
using namespace FlyCapture2;
//using namespace FlyCapture2;

#define CAM_WIDTH 1024
#define CAM_HEIGHT 1024

class Point_grey_capture : public Camera_capture{
private:
	void set_frame();
	Camera camera;
	void init_camera();
	Format7Info cam_info;
	void set_cam_info();
	void config_cam();
public:
	Point_grey_capture() {init_camera();}
};

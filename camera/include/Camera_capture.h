#pragma once

#include <opencv2/opencv.hpp>
#include "Component_finder.h"

using namespace cv;
using namespace std;

#define MIN_AREA 10000

class Camera_capture{

protected:
	int cap_width, cap_height, out_width, out_height;
	Mat frame;
	vector<Mat> images;
	Component_finder finder;
	enum Capture_state{NO_OBJECT,NEW_OBJECT,OLD_OBJECT};
	Capture_state state = NO_OBJECT;

	virtual void init_camera() = 0;
	virtual void set_frame() = 0;
	bool process_user_input();
	void add_image_of_object();
	Mat get_cropped_image(Point center);
	void display_frame();
	void set_camera_params();
	void check_object();
	void update_state();

public:
	Camera_capture() {}
	void set_capture_size(int width, int height) {cap_width = width;cap_height = height;}
	void set_out_size(int width, int height) {out_width = width;out_height = height;}
	bool tick();
	Mat get_next_object();
	vector<Mat> get_images(){return images;}
};


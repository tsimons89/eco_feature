#include "Camera_capture.h"

bool Camera_capture::tick(){
	set_frame();
	display_frame();
	check_object();
    return process_user_input();
}

bool Camera_capture::process_user_input(){
	switch((char)waitKey(30)){
	case '\n':
		return false;
	case '\e':
		exit(-1);
	}
	return true;
}

void Camera_capture::add_image_of_object(){
	Point object_center = finder.get_largest_component_center();
	Mat cropped_image =  get_cropped_image(object_center);
	images.push_back(cropped_image.clone());
}

Mat Camera_capture::get_cropped_image(Point center){
	int x =  (center.x - cap_width/2 < 0)                   ? 0 :
			 ((center.x + cap_width/2) > frame.cols)? frame.cols - cap_width:
  	  	 	 											  center.x - cap_width/2;

	int y =  (center.y - cap_height/2 < 0)                    ? 0 :
			 ((center.y + cap_height/2) > frame.rows)? frame.rows - cap_height: 
	                                                        center.y - cap_height/2;
	Rect crop_region(x,y,cap_width,cap_height);
	Mat cropped(frame,crop_region);
	resize(cropped,cropped,Size(out_width,out_height));
	return cropped;
}

void Camera_capture::display_frame(){
	Mat display_image = frame.clone();
	putText(display_image,"Images captured: " + to_string(images.size()),Point(10,20),FONT_HERSHEY_PLAIN,1.5,Scalar(0,0,255));
	putText(display_image,"Enter - save images",Point(10,60),FONT_HERSHEY_PLAIN,1.5,Scalar(0,0,255));
	putText(display_image,"Esc - exit",Point(10,80),FONT_HERSHEY_PLAIN,1.5,Scalar(0,0,255));
	imshow("Image capture", display_image);
}

void Camera_capture::check_object(){
	finder.set_image(frame);
	finder.set_largest_component();
	update_state();
}

void Camera_capture::update_state(){
	switch(state){
	case NO_OBJECT:
		if(finder.get_largest_component_area() >= MIN_AREA){
			state = NEW_OBJECT;
		}
		break;
	case NEW_OBJECT:
		if(finder.get_largest_component_center().y < frame.rows/2){
			state = OLD_OBJECT;
			add_image_of_object();
		}
		break;
	case OLD_OBJECT:
		if(finder.get_largest_component_area() < MIN_AREA)
			state = NO_OBJECT;
		break;
	}
}

Mat Camera_capture::get_next_object(){
	images.clear();
	while(images.size() < 1)
		tick();
	return images.front();
}

#include <opencv2/opencv.hpp>
#include "Camera_options.h"
#include "Camera_capture.h"
#include "Image_writer.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
	Camera_options options;
	options.parse_capture_options(argc,argv);
	Image_writer iw = options.get_image_writer();
	Camera_capture* cc_ptr = options.get_camera_cap_ptr();
    while(1){
		if(!cc_ptr->tick())
			break;
	}
	iw.write_images(cc_ptr->get_images());
    return 0;	
}

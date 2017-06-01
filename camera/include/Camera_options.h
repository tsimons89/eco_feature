#include <boost/program_options.hpp>
#include "Camera_capture.h"
#include "Image_writer.h"

namespace po = boost::program_options;

class Camera_options{
private:
	po::variables_map vm;
	po::options_description capture_desc;
	Image_writer image_writer;
	Camera_capture * camera_cap_ptr;

	void add_capture_desc();
public:
	Camera_options();
	void parse_capture_options(int argc,char* argv[]);
	Camera_capture* get_camera_cap_ptr(){return camera_cap_ptr;}
	Image_writer get_image_writer(){return image_writer;}
};
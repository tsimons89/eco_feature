#include <boost/program_options.hpp>
#include "Camera_capture.h"
#include "Adaboost_model.hpp"

namespace po = boost::program_options;

class Demo_options{
private:
	po::variables_map vm;
	po::options_description desc;
	Camera_capture * camera_cap_ptr;

	void add_desc();
public:
	Demo_options();
	void parse_options(int argc,char* argv[]);
	Camera_capture* get_camera_cap_ptr(){return camera_cap_ptr;}
};
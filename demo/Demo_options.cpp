#include "Demo_options.h"
#include "Webcam_capture.h"
#include "Point_grey_capture.h"

Demo_options::Demo_options(){
	add_desc();
}

void Demo_options::add_desc(){
	desc.add_options()
	("help", "Produce this help message")
	("results_path,r", po::value<string>(),"Folder with training results")
	("capture_width,w", po::value<int>()->default_value(400),"Width of image captured")
	("capture_height,h", po::value<int>()->default_value(400),"Height of image captured")
	("data_width,W", po::value<int>()->default_value(100),"Width of image written to file")
	("data_height,H", po::value<int>()->default_value(100),"Height of image written to file")
	("use_point_grey,g", po::value<bool>()->default_value(true),"Is the camera being used a Point Grey camera")
	;
}

void Demo_options::parse_options(int argc,char* argv[]){
	po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        exit(0);
    }
	Adaboost_model::set_results_path(vm["results_path"].as<string>());
    if(vm["use_point_grey"].as<bool>()){
		camera_cap_ptr = new Point_grey_capture();
    }
	else
		camera_cap_ptr = new Webcam_capture();
	camera_cap_ptr->set_capture_size(vm["capture_width"].as<int>(),vm["capture_height"].as<int>());
	camera_cap_ptr->set_out_size(vm["data_width"].as<int>(),vm["data_height"].as<int>());
}
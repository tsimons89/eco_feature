#include "Camera_options.h"
#include "Webcam_capture.h"
#include "Point_grey_capture.h"

Camera_options::Camera_options(){
	add_capture_desc();
}

void Camera_options::add_capture_desc(){
	capture_desc.add_options()
	("help", "Produce this help message")
	("capture_width,w", po::value<int>()->default_value(400),"Width of image captured")
	("capture_height,h", po::value<int>()->default_value(400),"Height of image captured")
	("write_width,W", po::value<int>()->default_value(100),"Width of image written to file")
	("write_height,H", po::value<int>()->default_value(100),"Height of image written to file")
	("file_pattern,f", po::value<string>()->default_value("*.jpg"),"Pattern for image filenames. Must include valid extention and \'*\', which will be replace with #.")
	("file_dir,d", po::value<string>()->default_value("./"),"Path to where the files will be written")
	("use_point_grey,g", po::value<bool>()->default_value(true),"Is the camera being used a Point Grey camera")
	;
}

void Camera_options::parse_capture_options(int argc,char* argv[]){
	po::store(po::parse_command_line(argc, argv, capture_desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << capture_desc << "\n";
        exit(0);
    }

    if(vm["use_point_grey"].as<bool>())
		camera_cap_ptr = new Point_grey_capture();
	else
		camera_cap_ptr = new Webcam_capture();

	camera_cap_ptr->set_capture_size(vm["capture_width"].as<int>(),vm["capture_height"].as<int>());
	camera_cap_ptr->set_out_size(vm["write_width"].as<int>(),vm["write_height"].as<int>());

	if(Image_writer::is_file_pattern_valid(vm["file_pattern"].as<string>()))
		image_writer.set_file_pattern(vm["file_pattern"].as<string>());
	else{
		cout << "File pattern not valid\n";
		exit(-1);
	}

	image_writer.set_path(vm["file_dir"].as<string>());


}
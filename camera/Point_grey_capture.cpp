#include "Point_grey_capture.h"



void Point_grey_capture::init_camera(){
	camera.Connect( 0 );
	set_cam_info();
	config_cam();
	camera.StartCapture();
}

void Point_grey_capture::set_frame(){
	Image rawImage;
	if ( camera.RetrieveBuffer( &rawImage ) != PGRERROR_OK )
		cout << "----capture error----" << endl;

    Image rgbImage;
    rawImage.Convert( PIXEL_FORMAT_BGR, &rgbImage );
	unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize()/(double)rgbImage.GetRows();       
	frame = Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(),rowBytes).clone();
}

void Point_grey_capture::set_cam_info(){
    bool supported;
    cam_info.mode = MODE_0;
    camera.GetFormat7Info(&cam_info, &supported);	
}

void Point_grey_capture::config_cam(){
  Format7ImageSettings cam_settings;
    cam_settings.mode = MODE_0;
    cam_settings.offsetX = (cam_info.maxWidth - CAM_WIDTH)/2;
    cam_settings.offsetY = (cam_info.maxHeight - CAM_HEIGHT)/2;
    //cam_settings.width = cam_info.maxWidth/2;
    //cam_settings.height = cam_info.maxHeight/2;
    cam_settings.width = CAM_WIDTH;
    cam_settings.height = CAM_HEIGHT;
    cam_settings.pixelFormat = PIXEL_FORMAT_RGB8;

    bool valid;
    Format7PacketInfo fmt7PacketInfo;

    camera.ValidateFormat7Settings(&cam_settings, &valid, &fmt7PacketInfo);

    if (!valid)
        cout << "Format7 settings are not valid" << endl;

    camera.SetFormat7Configuration(&cam_settings, fmt7PacketInfo.recommendedBytesPerPacket);
}

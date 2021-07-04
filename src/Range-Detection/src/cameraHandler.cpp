#include "../include/cameraHandler.hpp"
#include "../include/debug.h"

CameraHandler::CameraHandler(/* args */){
}

CameraHandler::~CameraHandler(){
}

bool CameraHandler::setResolution(cv::VideoCapture cap, int width, int height, int fps, int codecCode){
    int codec;
    // Run `v4l2-ctl --list-formats-ext` to find your camera's available formats
    if (codecCode == CP_MJPG) codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); 
    else if (codecCode == CP_YUYV) codec = cv::VideoWriter::fourcc('Y', 'U', 'Y', 'V');
    else if (codecCode == CP_H264) codec = cv::VideoWriter::fourcc('H', '2', '6', '4');
    cap.set(cv::CAP_PROP_FOURCC, codec);

    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FPS, fps);

    int dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); 
    int dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps_counter = cap.get(cv::CAP_PROP_FPS);

    DMESS("After set, actual resolution of the video w:%d h:%d fps:%d", dWidth, dHeight, fps_counter); 
    return true;
}
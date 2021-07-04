#include "include/CameraHandler.hpp"

CameraHandler::CameraHandler(/* args */){
}

CameraHandler::~CameraHandler(){
}

bool CameraHandler::setResolution(cv::VideoCapture cap, int width, int height, int fps){
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // TODO: Maybe you need to 
    cap.set(cv::CAP_PROP_FOURCC, codec);
    cap.set(cv::CAP_PROP_FPS, fps);

    int dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); 
    int dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps_counter = cap.get(cv::CAP_PROP_FPS);

    cout << "Resolution of the video : " << dWidth << " x " << dHeight << " FPS: " << fps_counter << endl;
    return true;
}
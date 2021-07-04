#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

#define CP_MJPG 0
#define CP_YUYV 1
#define CP_H264 2

class CameraHandler{
private:
    /* data */
public:
    CameraHandler(/* args */);
    ~CameraHandler();
    bool setResolution(cv::VideoCapture cap, int width, int height, int fps = 30, int codecCode = CP_MJPG);
};

#endif //CAMERA_HPP
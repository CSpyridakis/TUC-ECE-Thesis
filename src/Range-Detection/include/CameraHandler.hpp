#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

class CameraHandler{
private:
    /* data */
public:
    CameraHandler(/* args */);
    ~CameraHandler();
    bool setResolution(cv::VideoCapture cap, int width, int height, int fps = 30);
};

#endif //CAMERA_HPP
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "include/CameraHandler.hpp"

using namespace cv;
using namespace std;



int main(int argc, char *argv[]){
    VideoCapture cap(0, CAP_V4L2);
    if (!cap.isOpened()){ cout << "Cannot open the video camera" << endl; return -1; } 
    setResolution(cap, 1920, 1080, 5);


    return 0;
}
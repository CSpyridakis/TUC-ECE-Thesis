#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "../include/CameraHandler.hpp"

using namespace cv;
using namespace std;



int main(int argc, char *argv[]){
    CameraHandler ch;
    VideoCapture cap(0, CAP_V4L2);
    if (!cap.isOpened()){ cout << "Cannot open the video camera" << endl; return -1; } 
    ch.setResolution(cap, 1920, 1080, 5);

    while(true){
        Mat img;
        if (!cap.read(img)){ cout << "Video camera is disconnected" << endl; break;}

        imshow("Image", img);
        if (waitKey(1) == 27){ cout << "Esc key is pressed by user. Stoppig the video" << endl; break; }
    }

    
    return 0;
}
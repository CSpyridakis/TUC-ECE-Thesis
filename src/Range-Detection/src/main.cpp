#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "../include/cameraHandler.hpp"
#include "../include/debug.h"
#include "../include/rangeLogic.h"

using namespace cv;

void helpmenu(){
    std::cerr << "[Usage]: EstimateBallRange <OPTION>... <OPTION>..." << std::endl << std::endl;
    std::cerr << "Detect ball and estimate its range from camera" << std::endl << std::endl;
    std::cerr << "[Options]:" << std::endl;
    std::cerr << "  -c                  select video format (0: MJPG, 1: YUYV, 2: H264)" << std::endl;
    std::cerr << "  -f                  give file to stream (relative path)" << std::endl;
    std::cerr << "  -h                  print this help menu and exit" << std::endl;
    std::cerr << "  -p                  set fps" << std::endl;
    std::cerr << "  -v                  give camera id to stream" << std::endl;
    std::cerr << "  -x                  give video's width" << std::endl;
    std::cerr << "  -y                  give video's height" << std::endl << std::endl;
    std::cerr << "[Example]:" << std::endl;
    std::cerr << "./EstimateBallRange -v 0 -x 1920 -y 1080 -p 30 -c 0" << std::endl;
}

int main(int argc, char* argv[]){
    // Input video details
    int video_cam = 0, video_w = 864, video_h = 480, video_fps = 30, video_form = CP_MJPG; 
    // int video_cam = 0, video_w = 1920, video_h = 1080, video_fps = 30, video_form = CP_MJPG; 
    std::string video_file = "";
    bool openFile = false;

    // Read input arguments
    int c;
    while ((c = getopt (argc, argv, "c:f:hp:v:w:x:y:")) != -1)
    switch (c){
        case 'c': video_form = atoi(optarg); break;
        case 'f': openFile = true; video_file = std::string(optarg); break;
        case 'h': helpmenu(); return 0;
        case 'p': video_fps = atoi(optarg); break;
        case 'v': video_cam = atoi(optarg); break;
        case 'x': video_w = atoi(optarg); break;
        case 'y': video_h = atoi(optarg); break;
        case '?':
            if (optopt == 'c') fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt)) fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default: abort ();
    }

#ifdef DEBUG_S
    std::cerr << YELLOW << "[DEBUG] " << NORMAL << ": Input stream: " ;
    if(openFile) std::cerr << video_file << std::endl;
    else std::cerr << video_cam << std::endl;
    DMESS("Input args: resolution %d x %d at %d fps and format %d.", video_w, video_h, video_fps, video_form);
#endif

    // Open video from camera/file or exit
    cv::VideoCapture cap;
    if(!openFile) cap.open(video_cam, cv::CAP_V4L2);
    else cap.open(video_file);
    if (!cap.isOpened()){ DMESS("Cannot open stream"); return -1;} 

    // Use this instance to handle camera actions (like resizing, set codec or fps)
    CameraHandler ch; 
    // Set camera's resolution, fps and format
    ch.setResolution(cap, video_w, video_h, video_fps, video_form);

    // Default values for filters' variables 
    int gaussianKernelSize = 3, gausianDerivX = 5, gausiaDerivY = 0, cannythr1 = 50, cannythr2 = 150;
#ifdef DEBUG_C
    createTrackers(gaussianKernelSize, gausianDerivX, gausiaDerivY, cannythr1, cannythr2);
#endif

    // While there are 
    while(true){
        cv::Mat img, imgGray, imgBlur, imgCanny, imgout;
        if (!cap.read(img)){ DMESS("Input has disconnected"); break;}

        // --------------------------------------------------------------------
        // Preprocessing 
#ifdef DEBUG_C
        fixTrackersValues(gaussianKernelSize);
#endif
        // Convert to gray scale
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY); 
        // Apply Gaussian Blur
        cv::GaussianBlur(imgGray, imgBlur, cv::Size(gaussianKernelSize, gaussianKernelSize), gausianDerivX, gausiaDerivY);
        // Detect edges
        cv::Canny(imgBlur, imgCanny, cannythr1, cannythr2);
        
        // --------------------------------------------------------------------
        // Detect ball
        std::vector<cv::Vec3f> circles;
        detectBall(imgBlur, circles);

        // --------------------------------------------------------------------
        // Find ball range
        // estimateDistance(img);

        // --------------------------------------------------------------------
        
        // Only on user mode display images
#ifdef DEBUG_S
            // If you are in DEBUG mode print basic axis and center point in camera
            cameraPrintInfo(img);
            drawCircles(img, imgout, circles);
            cv::imshow("Original", imgout);   // Original image with extra notes
            
            // ------ Intermediate images ------
            // cv::imshow("Blur", imgBlur);   
            // cv::imshow("Canny", imgCanny);
#endif
        if (cv::waitKey(1) == 27){ DMESS("Esc key is pressed by user. Exit!"); break;}
    }
    cv::destroyAllWindows();
    cap.release();
    return 0;
}
/*
*   ---------------------------------------------------------------------------
*
*   This project is part of thesis submitted in fulfillment of the requirements
*   for the diploma of Electrical and Computer Engineer
*
*   University:                Technical University of Crete (TUC) - GR
*   Engineer:                  Spyridakis Christos
*   Create Date:               2/7/2021
*   Last Update Date:          5/7/2021
*   Dependencies:              OpenCV 4.5.2 or later
*   Revision:                  0.1
*
*   ---------------------------------------------------------------------------
*/

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <unistd.h> // getopt

#include "../include/misc.hpp"
#include "../include/debug.h"
#include "../include/rangeLogic.h"

using namespace cv;

int main(int argc, char* argv[]){
    // Video details (here will be also stored input arguments)
    int camera_id = 0, video_width = 864, video_height = 480, video_fps = 30, video_form = CP_MJPG; 
    std::string video_file = "";
    bool openFile = false;

    // Read input arguments using getopt
    int c;
    while ((c = getopt (argc, argv, "c:f:hp:v:w:x:y:")) != -1)
    switch (c){
        case 'c': video_form = atoi(optarg); break;
        case 'f': openFile = true; video_file = std::string(optarg); break;
        case 'h': helpmenu(); return 0;
        case 'p': video_fps = atoi(optarg); break;
        case 'v': camera_id = atoi(optarg); break;
        case 'x': video_width = atoi(optarg); break;
        case 'y': video_height = atoi(optarg); break;
        case '?':
            if (optopt == 'c'){ EMESS("Option -%c requires an argument.\n", optopt); } 
            else if (isprint (optopt)) { EMESS("Unknown option `-%c'.\n", optopt); }
            else { EMESS("Unknown option character `\\x%x'.\n", optopt); }
            return 1;
        default: abort ();
    }

    // Print input arguments
#ifdef DEBUG_S
    DMESS("Input stream: ");
    if(openFile) std::cerr << video_file << std::endl;
    else std::cerr << camera_id << std::endl;
    DMESS("Input args: resolution %d x %d at %d fps and format %d.\n", video_width, video_height, video_fps, video_form);
#endif

    // Open video from camera/file or exit
    cv::VideoCapture cap;
    if(!openFile) cap.open(camera_id, cv::CAP_V4L2);
    else cap.open(video_file);
    if (!cap.isOpened()){ EMESS("Cannot open stream\n"); return -1;} 

    // Set camera's resolution, fps and format
    setResolution(cap, video_width, video_height, video_fps, video_form);

    // Default values for filters' variables 
    int gaussianKernelSize = 9, 
        gausianDerivX = 2, 
        gausiaDerivY = 2, 
        cannythr1 = 50, 
        cannythr2 = 150;

#ifdef DEBUG_C
    createTrackers(gaussianKernelSize, gausianDerivX, gausiaDerivY, cannythr1, cannythr2);
#endif

    // For each frame 
    while(true){
        cv::Mat img, imgGray, imgBlur, imgCanny, imgout;
        if (!cap.read(img)){ EMESS("Input has disconnected\n"); break;}

        // --------------------------------------------------------------------
        // --------------------------------------------------------------------
        // Preprocessing 
#ifdef DEBUG_C
        fixTrackersValues(gaussianKernelSize);
#endif
        // Convert to gray scale
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY); 
        // Apply Blur
        // cv::medianBlur(imgGray, imgBlur, 5);
        cv::GaussianBlur(imgGray, imgBlur, cv::Size(gaussianKernelSize, gaussianKernelSize), gausianDerivX, gausiaDerivY);
        // Detect edges
        cv::Canny(imgBlur, imgCanny, cannythr1, cannythr2);
        
        // --------------------------------------------------------------------
        // --------------------------------------------------------------------
        // Detect ball
        std::vector<cv::Vec3f> circles;
        bool ballsDetected = detectBall(imgCanny, circles);


        if(!ballsDetected){
#ifdef DEBUG_S
            DMESS("No ball detected.\n");
#endif
        }

        // --------------------------------------------------------------------
        // --------------------------------------------------------------------
        // Find ball range
        // estimateDistance(img);

        // --------------------------------------------------------------------
        
        // Display images on non debug mode 
#ifdef DEBUG_S
            cameraPrintInfo(img);               // Add basic axis and center point
            drawCircles(img, imgout, circles);  // Add detected circles
            cv::imshow("Original", imgout);     // Display RGB image with info
            
            // Intermediate images 
            cv::imshow("Blur", imgBlur);   
            cv::imshow("Canny", imgCanny);
#endif
        // Exit
        if (cv::waitKey(1) == 27){ DMESS("Esc key is pressed by user. Exit!\n"); break;}
    }
    cv::destroyAllWindows();
    cap.release();
    return 0;
}
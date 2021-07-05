#include <opencv2/opencv.hpp>

#include "../include/debug.h"

void cameraPrintInfo(cv::Mat &img){
    if(DEBUG_S){
        // Based on Mat resolution (x,y) find points of interest
        cv::Scalar greenColor(0, 255, 0);
        cv::Point middleUp(int(img.cols/2), 0);
        cv::Point middleDown(int(img.cols/2), img.rows);
        cv::Point middleLeft(0, int(img.rows/2));
        cv::Point middleRight(img.cols, int(img.rows/2));
        cv::Point center(int(img.cols/2), int(img.rows/2));

        // Display Axis
        cv::line(img, middleLeft, middleRight, greenColor);     // Vertical
        cv::line(img, middleUp, middleDown, greenColor);        // Horizontal
        cv::circle(img, center, 20, greenColor, 1);             // Small circle in center

        // Auxiliary text with useful info 
        std::string resTxt = "Resolution: [" + std::to_string(img.cols) + "x" + std::to_string(img.rows) + "]";
        cv::putText(img, resTxt, cv::Point(50, 50), cv::FONT_HERSHEY_DUPLEX, 1, greenColor, 1);
    }
}

void createTrackers(int& gaussianKernelSize, int& gaussianDerX, int& gaussianDerY, int& cannythr1, int& cannythr2){
    std::string trackersWindow = "Trackers Window";
    cv::namedWindow(trackersWindow);

    cv::createTrackbar("Gausian (Kernel Size):", trackersWindow, &gaussianKernelSize, 25);
    cv::createTrackbar("Gausian (Deriv X):", trackersWindow, &gaussianDerX, 20);
    cv::createTrackbar("Gausian (Deriv Y):", trackersWindow, &gaussianDerY, 20);

    cv::createTrackbar("Canny (threshold 1):", trackersWindow, &cannythr1, 20);
    cv::createTrackbar("Canny (threshold 2):", trackersWindow, &cannythr2, 200);
}

void fixTrackersValues(int& gaussianKernelSize){
    std::string trackersWindow = "Trackers Window";
    if(gaussianKernelSize == 0){
        gaussianKernelSize = 1;
        cv::setTrackbarPos("Gausian (Kernel Size):", trackersWindow, 1);
    }
    else if (gaussianKernelSize % 2 == 0){
        gaussianKernelSize = gaussianKernelSize - 1;
    }
}

void drawCircles(cv::Mat img, cv::Mat& outimg, std::vector<cv::Vec3f>& circles){
    outimg = img.clone();
    
    for( int k = 0; k < circles.size(); k++ ){
        cv::Scalar blueColor(255, 0, 0);
        cv::Scalar redColor(0, 0, 255);
        cv::Vec3i c = circles[k];       /// x: c[0], y:c[1], radius: c[2]
        cv::Point center(c[0], c[1]);
        DMESS("Circle[%d] - at (%d, %d) radius = %d px", k, (int)c[0], (int)c[1], (int)c[2])

        // circle center
        circle(outimg, center, 1, redColor, 2, cv::LINE_AA);
        // circle outline
        circle(outimg, center, c[2], blueColor, 2, cv::LINE_AA);
    }
}

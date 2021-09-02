#include "../include/rangeLogic.h"
#include "../include/debug.h"

bool detectBall(cv::Mat img, std::vector<cv::Vec3f>& circles){

    cv::HoughCircles(img, circles, cv::HOUGH_GRADIENT,
                        2,                  // Accumulator resolution 
                        img.cols,           // Min distance between circles
                        100,                 // Canny high threshold
                        100,                 // Threshold for center detection
                        0, 200);            // Min and max radius
    

    return !circles.empty();
}


void estimateDistance(std::vector<cv::Vec3f>& circles, double &distances){
    
}

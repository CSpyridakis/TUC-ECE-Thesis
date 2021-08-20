#include "../include/rangeLogic.h"
#include "../include/debug.h"

bool detectBall(cv::Mat img, std::vector<cv::Vec3f>& circles){
    // cv::HoughCircles(img, circles, cv::HOUGH_GRADIENT,
    //                     1,                  // Accumulator resolution 
    //                     img.rows,           // Min distance between circles
    //                     13,                 // Canny high threshold
    //                     19,                 // Threshold for center detection
    //                     0, 0);              // Min and max radius
    

    return !circles.empty();
}


void estimateDistance(std::vector<cv::Vec3f>& circles, double &distances){
    
}

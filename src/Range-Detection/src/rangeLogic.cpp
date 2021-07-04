#include "../include/rangeLogic.h"
#include "../include/debug.h"

void detectBall(cv::Mat img, std::vector<cv::Vec3f>& circles){
    cv::HoughCircles(img, circles, cv::HOUGH_GRADIENT,
                        2,                  // Accumulator resolution 
                        img.rows/10,        // Min distance between circles
                        200,                // Canny high threshold
                        100,                // Threshold for center detection
                        2, 300);            // Min and max radius
    
}


void estimateDistance(cv::Mat img){
    
}

void drawCircles(cv::Mat img, cv::Mat& outimg, std::vector<cv::Vec3f>& circles){
    outimg = img.clone();
    
    for( int k = 0; k < circles.size(); k++ ){
        cv::Scalar blueColor(255, 0, 0);
        cv::Vec3i c = circles[k];       /// x: c[0], y:c[1], radius: c[2]
        cv::Point center(c[0], c[1]);
        DMESS("Circle[%d] - at (%d, %d) radius = %d px", k, (int)c[0], (int)c[1], (int)c[2])

        // circle center
        circle(outimg, center, 1, blueColor, 2, cv::LINE_AA);
        // circle outline
        circle(outimg, center, c[2], blueColor, 2, cv::LINE_AA);
    }
}
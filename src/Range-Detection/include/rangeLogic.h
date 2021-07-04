#ifndef RANGE_LOGIC_H
#define RANGE_LOGIC_H

#include <opencv2/opencv.hpp>

void detectBall(cv::Mat img, std::vector<cv::Vec3f>& circles);

void estimateDistance(cv::Mat img);

void drawCircles(cv::Mat img, cv::Mat& outimg, std::vector<cv::Vec3f>& circles);

#endif //RANGE_LOGIC_H
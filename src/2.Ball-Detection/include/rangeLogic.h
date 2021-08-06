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

#ifndef RANGE_LOGIC_H
#define RANGE_LOGIC_H

#include <opencv2/opencv.hpp>

/**
 * \brief: Find balls in the given frame
 * 
 * \param:  Frame to 
 * \param: circles
 * 
 * \return: True if at least a single ball was detected or else return false
*/
bool detectBall(cv::Mat img, std::vector<cv::Vec3f>& circles);

/**
 * \brief:
 * 
 * \param:
*/
void estimateDistance(cv::Mat img);

#endif //RANGE_LOGIC_H


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

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

#define CP_MJPG 0
#define CP_YUYV 1
#define CP_H264 2

/**
 * \brief:
 * 
 * \param:
 * \param:
*/
void helpmenu();

/**
 * \brief:
 * 
 * \param:
 * \param:
 * 
 * \return:
*/
bool setResolution(cv::VideoCapture cap, int width, int height, int fps = 30, int codecCode = CP_MJPG);

#endif //CAMERA_HPP
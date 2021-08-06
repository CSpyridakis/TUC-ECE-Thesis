/*
*   ---------------------------------------------------------------------------
*
*   This project is part of thesis submitted in fulfillment of the requirements
*   for the diploma of Electrical and Computer Engineer
*
*   University:                Technical University of Crete (TUC) - GR
*   Engineer:                  Spyridakis Christos
*   Create Date:               16/7/2021
*   Last Update Date:          16/7/2021
*   Dependencies:              OpenCV 4.5.2 or later
*   Revision:                  0.1
*
*   ---------------------------------------------------------------------------
*/

#ifndef SETUP_H
#define SETUP_H

#include <opencv2/opencv.hpp>

#define BOARD_SIZE          cv::Size(7,9)
#define SQUARE_DIMENSION    0.02013f 

static float cameraCalibrationdata[9] = {1496.109661878852, 0, 539.5, 0, 1496.109661878852, 959.5,  0, 0, 1};
static float distCoeffsCalibrationdata[5] = {-0.2335183398761917, 0.06116931263162484, 0, 0, 0};


#endif //SETUP_H
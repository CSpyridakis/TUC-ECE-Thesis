#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <opencv2/opencv.hpp>

static float cameraCalibrationdata_1920x1080[9] = {1496.109661878852, 0, 539.5, 0, 1496.109661878852, 959.5,  0, 0, 1};
static float distCoeffsCalibrationdata_1920x1080[5] = {-0.2335183398761917, 0.06116931263162484, 0, 0, 0};

static float cameraCalibrationdata_1280x720[9] = {9.109805646939659e+02, 0.0, 6.632455180393422e+02, 0.0, 9.093556608232609e+02, 3.701867268352723e+02, 0.0, 0.0, 1.0};
static float distCoeffsCalibrationdata_1280x720[5] = {-0.030001703014775, 0.096520683369681, -0.001382953355924, -1.082003049159845e-04, -0.112295190373465};

static float cameraCalibrationdata_720x480[9] = {724.3190291450312, 0, 239.5, 0, 724.3190291450312, 431.5, 0, 0, 1};
static float distCoeffsCalibrationdata_720x480[5] = {-0.3672694758638776, 0.2817674563871566, 0, 0, 0};

static float cameraCalibrationdata_640x480[9] = {608.7864577371455, 0, 239.5, 0, 608.7864577371455, 319.5, 0, 0, 1};
static float distCoeffsCalibrationdata_640x480[5] = {-0.3345218539718484, 0.903762909314839, 0, 0, 0};


bool findCameraRemapMats(const cv::Size size, cv::Mat &mapX, cv::Mat &mapY, const int resolution){
    cv::Mat cameraMatrix, distCoeffs;
    if(resolution == RES_1920x1080){
        cameraMatrix = cv::Mat(3, 3, CV_32FC1, cameraCalibrationdata_1920x1080);
        distCoeffs = cv::Mat(1, 5, CV_32FC1, distCoeffsCalibrationdata_1920x1080);
    }
    else if (resolution == RES_1280x720){
        cameraMatrix = cv::Mat(3, 3, CV_32FC1, cameraCalibrationdata_1280x720);
        distCoeffs = cv::Mat(1, 5, CV_32FC1, distCoeffsCalibrationdata_1280x720);
    }
    else if (resolution == RES_720x480){
        cameraMatrix = cv::Mat(3, 3, CV_32FC1, cameraCalibrationdata_720x480);
        distCoeffs = cv::Mat(1, 5, CV_32FC1, distCoeffsCalibrationdata_720x480);
    }
    else if (resolution == RES_720x480){
        cameraMatrix = cv::Mat(3, 3, CV_32FC1, cameraCalibrationdata_720x480);
        distCoeffs = cv::Mat(1, 5, CV_32FC1, distCoeffsCalibrationdata_720x480);
    }
    else if (resolution == RES_640x480){
        cameraMatrix = cv::Mat(3, 3, CV_32FC1, cameraCalibrationdata_640x480);
        distCoeffs = cv::Mat(1, 5, CV_32FC1, distCoeffsCalibrationdata_640x480);
    }
    else
        return false;
    

    cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), cameraMatrix, size, CV_32FC1, mapX, mapY);
    return true;
}
#endif //CALIBRATION_H
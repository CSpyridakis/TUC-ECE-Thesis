/*
*   ---------------------------------------------------------------------------
*
*   This project is part of thesis submitted in fulfillment of the requirements
*   for the diploma of Electrical and Computer Engineer
*
*   University:                Technical University of Crete (TUC) - GR
*   Engineer:                  Spyridakis Christos
*   Create Date:               8/7/2021
*   Last Update Date:          16/7/2021
*   Dependencies:              OpenCV 4.5.2 or later
*   Revision:                  0.1
*
*   ---------------------------------------------------------------------------
*/
#ifndef CAMERA_CALIBRATION_H
#define CAMERA_CALIBRATION_H

#include <opencv2/opencv.hpp>
#include "debug.h"
#include "misc.hpp"
#include <ctime>

/**
 * @brief
 * @param
 * @param
 */
int createDataset(const std::string folderName, const cv::Size chessboardDimensions, const int video_width, const int video_height, const int camera_id = 0, const float timeBtPhotos = 2, const int imgsNum = 30, const int video_form = 0, const int video_fps = 30){

    // Open camera or exit
    cv::VideoCapture cap;
    cap.open(camera_id, cv::CAP_V4L2);
    if (!cap.isOpened()){ EMESS("Cannot open camera"); return -1;} 

    // Set camera's resolution, fps and format
    setResolution(cap, video_width, video_height, video_fps, video_form);

    // ------------------------------------------------------------------------
    // Create or Delete data contents if folder already exists
    //
    system(("rm -rf " + folderName + " && mkdir -p " + folderName).c_str());

    // ------------------------------------------------------------------------
    // Take imgsNum photos, one every timeBtPhotos seconds
    //
    DMESS("Take %d photos, every %.2f seconds", imgsNum, timeBtPhotos);
    
    int imgCounter = 1;
    cv::Mat img, imgGray;
    std::vector<cv::Point2f> corners;
    bool foundChessboard = true;
    clock_t lastCl = clock(); 
    while(true){
        if (!cap.read(img)){EMESS("Input has disconnected"); break;}
        if(imgCounter > imgsNum) break; // Exit 

#ifdef DEBUG_C
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
        foundChessboard = cv::findChessboardCorners(imgGray, chessboardDimensions, corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);
#endif

        // Every timeBtPhotos seconds
        if(foundChessboard && (clock() - lastCl)/(double)CLOCKS_PER_SEC > timeBtPhotos){
            DMESS("Take photo %d/%d", imgCounter, imgsNum);
            std::string imgName = folderName + "/img" + std::to_string(imgCounter) + ".png";
            cv::imwrite(imgName, img);

            cv::circle(img, cv::Point(int(img.cols/2), int(img.rows/2)), int(img.rows/10), cv::Scalar(0, 0, 255), cv::FILLED);
            cv::circle(img, cv::Point(int(img.cols/2), int(img.rows/2)), int(img.rows/30), cv::Scalar(255, 255, 255), cv::FILLED);
        
            imgCounter++;
            lastCl = clock();
            cv::imshow("Original", img);
        }else if((clock() - lastCl)/(double)CLOCKS_PER_SEC > 0.1)
            cv::imshow("Original", img);
        
        if (cv::waitKey(1) == 27){ DMESS("Esc key is pressed by user. Exit!"); break;}
    }

    cv::destroyAllWindows();
    cap.release();
}


// [DEBUG] : Valid images are 11. Begin Calibration...
// intrinsicMatrix : [1185.777855814654, 0, 547.49575806643;
//  0, 1265.658701057108, 906.5493764006484;
//  0, 0, 1]
// distCoeffs : [-0.0007322861698132749, -0.02188488141160843, 0.01820508111982341, -0.03281229620621096, 0.005712609878082597]

// [DEBUG] : Valid images are 47. Begin Calibration...
// intrinsicMatrix : [1800.936965129956, 0, 696.1242205703089;
//  0, 1800.961799765369, 708.5973066042861;
//  0, 0, 1]
// distCoeffs : [-0.002716396560153968, 0.2293808193662089, 0.02226005045854939, -0.03104624188697552, -0.2480605993413657]

// [DEBUG] : Valid images are 94. Begin Calibration...
// intrinsicMatrix : [1574.312106469767, 0, 646.797345228185;
//  0, 1574.142710655664, 847.7187521150353;
//  0, 0, 1]

// distCoeffs : [-0.06101324133001612, 0.1310067282250084, 0.02292885491796105, -0.04099213981890655, -0.08268354895899227]

/**
 * @brief
 * @param
 * @param
 * 
 * @see The code below created based on OpenCV official site calibration tutorial https://docs.opencv.org
 */
int createIntrinsicParametersFile(const std::string folderName, const cv::Size chessboardDimensions, const float squareDimension){    
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;

    std::vector<cv::Point3f> objp;
    for(int i = 0; i<chessboardDimensions.height; i++)
        for(int j = 0; j<chessboardDimensions.width; j++)
            objp.push_back(cv::Point3f(i*squareDimension,j*squareDimension,0));

    // Create vector to store all images names
    std::vector<cv::String> imgNames;
    cv::glob(("./" + folderName + "/*.png"), imgNames);
    
    cv::Mat img, imgGray;
    int validImages=0;
    std::vector<cv::Point2f> corners;
    // For each calibration image
    for(int i{0}; i< imgNames.size(); i++){
       img = cv::imread(imgNames[i]);

        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
        
        bool foundChessboard = cv::findChessboardCorners(imgGray, chessboardDimensions, corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

        if(foundChessboard){
            cv::cornerSubPix(imgGray, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.001));
            objectPoints.push_back(objp);
            imagePoints.push_back(corners);
            DMESS("Found pattern on image %s", (imgNames[i]).c_str());
            validImages++;
        }  
        
#ifdef DEBUG_C
        cv::drawChessboardCorners(img, chessboardDimensions, cv::Mat(corners), foundChessboard);
        cv::imshow("Original", img);
        if (cv::waitKey(1) == 27){ DMESS("Esc key is pressed by user. Exit!\n"); break;}
#endif
    }
	cv::destroyAllWindows();   

    DMESS("Valid images are %d. Begin Calibration...", validImages);
    cv::Mat cameraMatrix, distCoeffs, rotationMatrix, translationMatrix, newCameraMatrix;

    if(validImages<1){EMESS("Too low number of valid images. Please take more chessboard images."); return -1;}
    cv::calibrateCamera(objectPoints, imagePoints, cv::Size(imgGray.rows,imgGray.cols), cameraMatrix, distCoeffs, rotationMatrix, translationMatrix, cv::CALIB_FIX_ASPECT_RATIO + cv::CALIB_FIX_K3 + cv::CALIB_ZERO_TANGENT_DIST + cv::CALIB_FIX_PRINCIPAL_POINT);

    // std::cout << "intrinsicMatrix : " << intrinsicMatrix << std::endl << std::endl;
    // std::cout << "distCoeffs : " << distCoeffs << std::endl << std::endl;
    // std::cout << "Rotation vector : " << rotationMatrix << std::endl << std::endl;
    // std::cout << "Translation vector : " << translationMatrix << std::endl << std::endl;


    cv::Mat mapX, mapY;
    cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), cameraMatrix, cv::Size(img.cols, img.rows), CV_32FC1, mapX, mapY);

    ////////////////////////
    cv::VideoCapture cap;
    cap.open(0, cv::CAP_V4L2);
    if (!cap.isOpened()){ EMESS("Cannot open camera"); return -1;} 
    setResolution(cap, 1920, 1080, 30, 0);

    cv::Mat undimg;
    while(true){
        if (!cap.read(img)){EMESS("Input has disconnected"); break;}

        cv::remap(img, undimg, mapX, mapY, cv::INTER_LINEAR);
        cv::imshow("Original", img);
        cv::imshow("Remaped", undimg);
        if (cv::waitKey(1) == 27){ DMESS("Esc key is pressed by user. Exit!"); break;}
    }

    cv::destroyAllWindows();
    cap.release();
}

#endif //CAMERA_CALIBRATION_H
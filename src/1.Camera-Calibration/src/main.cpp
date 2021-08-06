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

#include <opencv2/opencv.hpp>
#include <unistd.h> // getopt

#include "../include/cameraCalibration.h"
#include "../include/setup.h"

int main(int argc, char* argv[]){
    bool takeImages         = false;
    bool createIntrinsic    = true;

    // Video details (here will be also stored input arguments)
    int camera_id = 0, video_width = 864, video_height = 480, video_fps = 30, video_form = CP_MJPG; 
    std::string folder = "data";
    float timeBtPhotos = 2.0;
    int imgsNum = 10;
    
    // Read input arguments using getopt
    int c;
    while ((c = getopt (argc, argv, "c:Df:hIn:p:t:v:w:x:y:")) != -1)
        switch (c){
            case 'c': video_form = atoi(optarg);    break;
            case 'D': takeImages = true;            break;
            case 'f': folder = optarg;              break;
            case 'h': helpmenu();                   return 0;
            case 'I': createIntrinsic = true;       break;
            case 'n': imgsNum = atoi(optarg);       break;
            case 'p': video_fps = atoi(optarg);     break;
            case 't': timeBtPhotos = atof(optarg);  break;
            case 'v': camera_id = atoi(optarg);     break;
            case 'x': video_width = atoi(optarg);   break;
            case 'y': video_height = atoi(optarg);  break;
            case '?':
                if (optopt == 'c'){ EMESS("Option -%c requires an argument.", optopt); } 
                else if (isprint (optopt)) { EMESS("Unknown option `-%c'.", optopt); }
                else { EMESS("Unknown option character `\\x%x'.", optopt); }
                return 1;
            default: abort ();
        }
    
    if(takeImages){
        DMESS("Input args: resolution %d x %d at %d fps, format %d | Photos: %d, every %.2f secs.", video_width, video_height, video_fps, video_form, imgsNum, timeBtPhotos);
        createDataset(folder, BOARD_SIZE, video_width, video_height, camera_id, timeBtPhotos, imgsNum, video_form, video_fps);
    }
    else if(createIntrinsic){
        createIntrinsicParametersFile(folder, BOARD_SIZE, SQUARE_DIMENSION);
    }
    
    return 0;
}
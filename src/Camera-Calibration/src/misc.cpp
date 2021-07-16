#include "../include/misc.hpp"
#include "../include/debug.h"

void helpmenu(){
    std::cerr << "[Usage]: CalibrateCamera -D <OPTION>... <OPTION>..." << std::endl;
    std::cerr << "[Usage]: CalibrateCamera -I <OPTION>... <OPTION>..." << std::endl << std::endl;
    std::cerr << "Calibrate Camera" << std::endl << std::endl;
    std::cerr << "[Options]:" << std::endl;
    std::cerr << "  -c  formatNumber    select video format (0: MJPG, 1: YUYV, 2: H264)" << std::endl;
    std::cerr << "  -D                  create dataset" << std::endl;
    std::cerr << "  -h                  print this help menu and exit" << std::endl;
    std::cerr << "  -I                  find and export intrinsic parameters" << std::endl;
    std::cerr << "  -p  fpsNumber       set fps" << std::endl;
    std::cerr << "  -v  id              give camera id to stream" << std::endl;
    std::cerr << "  -x  width           give video's width" << std::endl;
    std::cerr << "  -y  height          give video's height" << std::endl << std::endl;
    std::cerr << "[Example]:" << std::endl;
    std::cerr << "./EstimateBallRange -v 0 -x 1920 -y 1080 -p 30 -c 0" << std::endl;
}

bool setResolution(cv::VideoCapture cap, int width, int height, int fps, int codecCode){
    int codec;
    // Run `v4l2-ctl --list-formats-ext` to find your camera's available formats
    if (codecCode == CP_MJPG) codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); 
    else if (codecCode == CP_YUYV) codec = cv::VideoWriter::fourcc('Y', 'U', 'Y', 'V');
    else if (codecCode == CP_H264) codec = cv::VideoWriter::fourcc('H', '2', '6', '4');
    cap.set(cv::CAP_PROP_FOURCC, codec);

    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FPS, fps);

    int dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); 
    int dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps_counter = cap.get(cv::CAP_PROP_FPS);

    DMESS("After set, actual resolution of the video w:%d h:%d fps:%d", dWidth, dHeight, fps_counter); 
    return true;
}
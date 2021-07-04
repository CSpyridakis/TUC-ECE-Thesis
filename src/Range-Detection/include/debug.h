#ifndef DEBUG_H
#define DEBUG_H

#include <opencv2/opencv.hpp>
#include <cstdio>

// TODO: You may need to change these macros for production
#define DEBUG_S true    // Print debug messages
#define DEBUG_C         // Configuration Mode (commend out to disable it)

// Buffer size for messages
#define BUFSIZE 1024

// Colors for stderr messages
#define YELLOW  "\033[33;1m"
#define NORMAL  "\033[0m"

// Use this function to print debug messages (use it like printf function)
#define DMESS(mess...){if(DEBUG_S){\
                        char infoBuffer[BUFSIZE]; \
                        snprintf(infoBuffer, sizeof(infoBuffer), mess);\
                        fprintf(stderr, "%s[DEBUG]%s : %s\n", YELLOW, NORMAL, infoBuffer );}}

// ---------------
void cameraPrintInfo(cv::Mat &img);
void createTrackers(int& gaussianKernelSize, int& gaussianDerX, int& gaussianDerY, int& cannythr1, int& cannythr2);
void fixTrackersValues(int& gaussianKernelSize);

#endif //DEBUG_H
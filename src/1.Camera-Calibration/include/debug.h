/*
*   ---------------------------------------------------------------------------
*
*   This project is part of thesis submitted in fulfillment of the requirements
*   for the diploma of Electrical and Computer Engineer
*
*   University:                Technical University of Crete (TUC) - GR
*   Engineer:                  Spyridakis Christos
*   Create Date:               2/7/2021
*   Last Update Date:          16/7/2021
*   Dependencies:              OpenCV 4.5.2 or later
*   Revision:                  0.1
*
*   ---------------------------------------------------------------------------
*/

#ifndef DEBUG_H
#define DEBUG_H

#include <opencv2/opencv.hpp>
#include <cstdio>

// TODO: You may need to change these macros for production
#define DEBUG_S true    // Print debug messages
// #define DEBUG_C         // Configuration Mode (commend out to disable it)

// Buffer size for messages
#define BUFSIZE 1024

// Colors for stderr messages
#define RED     "\033[31;1m"
#define GREEN   "\033[32;1m"
#define YELLOW  "\033[33;1m"
#define NORMAL  "\033[0m"

#define MESSAGE(type, color, newline, mess...){ char infoBuffer[BUFSIZE]; \
                        snprintf(infoBuffer, sizeof(infoBuffer), mess);\
                        fprintf(stderr, "%s[%s]%s : %s%s", color, type, NORMAL, infoBuffer, newline);\
                        }

// Use this function to print debug messages (use it as you would use printf)
#define DMESS(mess...)  MESSAGE("DEBUG", YELLOW, "\n", mess)
#define DMESSN(mess...) MESSAGE("DEBUG", YELLOW, "", mess)

#define EMESS(mess...)  MESSAGE("ERROR", RED, "\n", mess)
#define EMESSN(mess...) MESSAGE("ERROR", RED, "", mess)

#define IMESS(mess...)  MESSAGE("INFO ", GREEN, "\n", mess)
#define IMESSN(mess...) MESSAGE("INFO ", GREEN, "", mess)


#endif //DEBUG_H
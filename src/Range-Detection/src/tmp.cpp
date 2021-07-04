#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


#define WINDOW_PROPERTIES_ENABLED
// #define QT_ENABLED

#define NUMBER_OF_COLOR_BALLS   4
#define PURPLE_CLR              0
#define GREEN_CLR               1
#define YELLOW_CLR              2
#define WHITE_CLR               3

#define HSV_VALUES              3
#define H_V                     0
#define S_V                     1
#define V_V                     2

#define MIN_MAX                 2
#define MIN_V                   0
#define MAX_V                   1


int ballColorsLimits[NUMBER_OF_COLOR_BALLS][HSV_VALUES][MIN_MAX] = {
        //      HUE            Saturation            Value
        {{164   , 174 },    {60     , 255},     {130    , 237}},    // Purple Ball
        {{54    , 77},      {103    , 223},     {123    , 230}},    // Green Ball
        {{23    , 33},      {129    , 255},     {137    , 194}},    // Yellow Ball
        {{17    , 97},      {0      , 66},      {134    , 250}}     // White Ball
};

bool setResolution(cv::VideoCapture cap, int width, int height, int fps = 30){
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cap.set(cv::CAP_PROP_FOURCC, codec);
    cap.set(cv::CAP_PROP_FPS, fps);

    int dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); 
    int dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps_counter = cap.get(cv::CAP_PROP_FPS);

    cout << "Resolution of the video : " << dWidth << " x " << dHeight << " FPS: " << fps_counter << endl;
    return true;
}

#if (defined QT_ENABLED)
void onPurpleColor(int state, void* p){

}
void onGreenColor(int state, void* p){

}
void onYellowColor(int state, void* p){

}
void onWhiteColor(int state, void* p){

}
#endif

void getContours(Mat imgDlt, Mat img){
    
}

int main(int argc, char* argv[]){
    VideoCapture cap(0, CAP_V4L2);
    if (!cap.isOpened()){ cout << "Cannot open the video camera" << endl; return -1; } 
    setResolution(cap, 1920, 1080, 5);
    
    Mat img;
    Mat imgGray, imgBlur, imgCanny, imgDlt;
    
    String HSV_Window = "HSV";
    namedWindow(HSV_Window);

    int color_pick = 0;
    int last_color_pick = color_pick;

#if (defined WINDOW_PROPERTIES_ENABLED)
    createTrackbar("Color(0:Purple, 1:Green, 2:Yellow, 3:White):", HSV_Window, &color_pick, 3);

    // HSV values
    int hmin = ballColorsLimits[PURPLE_CLR][H_V][MIN_V] , smin = ballColorsLimits[PURPLE_CLR][S_V][MIN_V] , vmin = ballColorsLimits[PURPLE_CLR][V_V][MIN_V];
    int hmax = ballColorsLimits[PURPLE_CLR][H_V][MAX_V] , smax = ballColorsLimits[PURPLE_CLR][S_V][MAX_V] , vmax = ballColorsLimits[PURPLE_CLR][V_V][MAX_V];
    createTrackbar("HMIN:", HSV_Window, &hmin, 179);
    createTrackbar("HMAX:", HSV_Window, &hmax, 179);
    createTrackbar("SMIN:", HSV_Window, &smin, 255);
    createTrackbar("SMAX:", HSV_Window, &smax, 255);
    createTrackbar("VMIN:", HSV_Window, &vmin, 255);
    createTrackbar("VMAX:", HSV_Window, &vmax, 255);
    
    //
    int gaussianKernelSize = 1;
    int gausianDerivX = 5;
    int gausiaDerivY = 0;
    createTrackbar("Gausian (Kernel Size):", HSV_Window, &gaussianKernelSize, 25);
    createTrackbar("Gausian (Deriv X):", HSV_Window, &gausianDerivX, 20);
    createTrackbar("Gausian (Deriv Y):", HSV_Window, &gausiaDerivY, 20);

    //

    int dltSize = 1;
    int ersSize = 1;
    createTrackbar("Diletion (CLR):", HSV_Window, &dltSize, 20);
    createTrackbar("Erosion (CLR):", HSV_Window, &ersSize, 20);

    cout << "Trackbars added" << endl;

    #if (defined QT_ENABLED)
        // Color Ball Choose
        createButton("Purple",onPurpleColor,NULL,QT_PUSH_BUTTON,1);
        createButton("Green",onGreenColor,NULL,QT_PUSH_BUTTON,0);
        createButton("Yellow",onYellowColor,NULL,QT_PUSH_BUTTON,0);
        createButton("White",onWhiteColor,NULL,QT_PUSH_BUTTON,0);
        cout << "QT radioboxes added" << endl;
    #endif
#endif

    while(true){
        Mat img;
        if (!cap.read(img)){ cout << "Video camera is disconnected" << endl; break;}
        
        if(last_color_pick != color_pick){
            hmin = ballColorsLimits[color_pick][H_V][MIN_V];
            smin = ballColorsLimits[color_pick][S_V][MIN_V];
            vmin = ballColorsLimits[color_pick][V_V][MIN_V];
            
            hmax = ballColorsLimits[color_pick][H_V][MAX_V]; 
            smax = ballColorsLimits[color_pick][S_V][MAX_V];
            vmax = ballColorsLimits[color_pick][V_V][MAX_V];
            last_color_pick = color_pick;
            
            if(color_pick == 0)         cout << "Color changed to: Purple" << endl;
            else if(color_pick == 1)    cout << "Color changed to: Green" << endl;
            else if(color_pick == 2)    cout << "Color changed to: Yellow" << endl;
            else if(color_pick == 3)    cout << "Color changed to: White" << endl;
            else                        cout << "There is a problem" << endl;

            setTrackbarPos("HMIN:", HSV_Window, hmin);
            setTrackbarPos("HMAX:", HSV_Window, hmax);
            setTrackbarPos("SMIN:", HSV_Window, smin);
            setTrackbarPos("SMAX:", HSV_Window, smax);
            setTrackbarPos("VMIN:", HSV_Window, vmin);
            setTrackbarPos("VMAX:", HSV_Window, vmax);
        }

        Mat imgBlur;
        if(gaussianKernelSize == 0){
            gaussianKernelSize = 1;
            setTrackbarPos("Gausian (Kernel Size):", HSV_Window, 1);
        }
        else if (gaussianKernelSize % 2 == 0){
            gaussianKernelSize = gaussianKernelSize - 1;
        }
        GaussianBlur(img, imgBlur, Size(gaussianKernelSize, gaussianKernelSize), gausianDerivX, gausiaDerivY);
        
        if(dltSize == 0){
            dltSize = 1;
            setTrackbarPos("Diletion (CLR):", HSV_Window, 1);
        }
        else if (dltSize % 2 == 0){
            dltSize = dltSize - 1;
        }
        if(ersSize == 0){
            ersSize = 1;
            setTrackbarPos("Erosion (CLR):", HSV_Window, 1);
        }
        else if (ersSize % 2 == 0){
            ersSize = ersSize - 1;
        }
        //
        Mat imgHSV, mask;
        cvtColor(imgBlur, imgHSV, COLOR_BGR2HSV);
        Scalar colorLowerLimit(hmin, smin, vmin);
        Scalar colorUpperLimit(hmax, smax, vmax);

        inRange(imgHSV, colorLowerLimit, colorUpperLimit, mask);
        //

        Mat imgDlt, imgErs;
        Mat kernelDlt = getStructuringElement(MORPH_RECT, Size(dltSize,dltSize));
        Mat kernelErs = getStructuringElement(MORPH_RECT, Size(ersSize,ersSize));
        dilate(mask, imgDlt, kernelDlt);
        erode(imgDlt, imgErs, kernelErs);
        //
        Mat imgGray, imgBlurG, imgCanny, imgDltG, imgErsG;
        Canny(mask, imgCanny, 25, 75);

        dilate(imgCanny, imgDltG, kernelDlt);
        erode(imgDltG, imgErsG, kernelErs);
        //
        // Mat imgGray, imgBlurG, imgCanny, imgDltG;
        // cvtColor(img, imgGray, COLOR_BGR2GRAY);
        // GaussianBlur(imgGray, imgBlurG, Size(3,3), 3, 0);
        // Canny(imgBlurG, imgCanny, 25, 75);
        // Mat kernelDltG = getStructuringElement(MORPH_RECT, Size(3,3)); // On size use odd numbers
        // dilate(imgCanny, imgDltG, kernelDltG);

        // // ----- Main Processing -----
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        findContours(imgDltG, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        vector<vector<Point>> conPoly(contours.size());

        

        for(int i=0; i<contours.size();i++){
            int area = contourArea(contours[i]);
            vector<Rect> boundRect(contours.size());
            String objType;

            // Create Approximation polygons from shapes
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.1*peri, true);

            boundRect[i] = boundingRect(conPoly[i]);
            int objCon = (int)conPoly[i].size();

            // if(objCon > 100)         objType = "circle";

            // objType = "55cm";

            // Draw contours
            // drawContours(img, conPoly, i, Scalar(0, 0, 0), 2);
            // Draw rectangle around shapes
            // rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 255));
            // Write down text on each shape
            // putText(img, objType, {boundRect[i].x,boundRect[i].y-5}, FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 2);
        }
        // imshow("image", img);
        
        Mat matMask, matDisplayConcat, allMats;
        cvtColor(imgErs,matMask,COLOR_GRAY2BGR);
        // hconcat(imgBlur, matMask, matDisplayConcat); // horizontal     
        // hconcat(matDisplayConcat, img, allMats); // horizontal     
        hconcat(img, matMask, allMats); // horizontal     
        // imshow("HSV", matDisplayConcat);
        imshow("HSV", allMats);
        if (waitKey(1) == 27){ cout << "Esc key is pressed by user. Stoppig the video" << endl; break; }
    }

    return 0;
}


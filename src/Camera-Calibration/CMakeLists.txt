cmake_minimum_required(VERSION 2.8)
project( CameraCalibration )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(FilesToInclude 
src/main.cpp
)
add_executable(${PROJECT_NAME} ${FilesToInclude})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

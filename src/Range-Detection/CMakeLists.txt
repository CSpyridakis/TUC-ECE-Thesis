cmake_minimum_required(VERSION 2.8)
project( EstimateBallRange )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(FilesToInclude 
src/main.cpp
src/misc.cpp
src/debug.cpp
src/rangeLogic.cpp
)
add_executable(${PROJECT_NAME} ${FilesToInclude})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

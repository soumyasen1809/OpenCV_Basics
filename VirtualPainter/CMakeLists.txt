cmake_minimum_required(VERSION 2.8)
project( virtualpainter )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( virtualpainter virtualpainter.cpp )
target_link_libraries( virtualpainter ${OpenCV_LIBS} )

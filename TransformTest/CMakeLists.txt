cmake_minimum_required(VERSION 3.5 )
set(CMAKE_CXX_STANDARD 11)
project( testvideo )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(testvideo TransformTest.cpp )
target_link_libraries( testvideo ${OpenCV_LIBS})


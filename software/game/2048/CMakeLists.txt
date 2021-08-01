cmake_minimum_required(VERSION 3.0.0)
project(2048 CXX)

find_package(OpenCV REQUIRED)

add_executable( 2048 2048.cpp )

set(LIBS ${OpenCV_LIBS})
target_link_libraries( 2048 ${LIBS} )
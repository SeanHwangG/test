cmake_minimum_required(VERSION 3.0.0)
project(debug VERSION 0.1.0)
set(CMAKE_VERBOSE_MAKEFILE ON) # show compiler command

find_package( glog REQUIRED )

include(CTest)
enable_testing()

add_executable(debug main.cpp)
add_compile_definitions(VAR=value)

target_link_libraries (debug glog::glog)
cmake_minimum_required(VERSION 3.0.0)
project(snake CXX)

find_package(OpenCV REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(snake ${SOURCES})
include_directories(include)

set(LIBS ${OpenCV_LIBS})
target_link_libraries(snake ${LIBS} )
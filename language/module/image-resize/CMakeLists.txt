cmake_minimum_required(VERSION 3.0.0)
project(main CXX)

find_package(OpenCV REQUIRED)

include_directories("/usr/local/Cellar/opencv/4.5.0/include/opencv4")
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
set(CMAKE_CXX_STANDARD 17)
add_executable(main ${SOURCES})


set(LIBS ${OpenCV_LIBS})
target_link_libraries(main ${LIBS} )
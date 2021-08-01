cmake_minimum_required(VERSION 3.0.0)
project(tictactoe)

find_package( OpenCV REQUIRED )

add_executable(main main.cpp)
include_directories(.)

set(LIBS ${OpenCV_LIBS})
target_link_libraries( main ${LIBS} )

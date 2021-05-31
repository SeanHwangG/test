cmake_minimum_required(VERSION 3.0.0)
project(falppy_bot)

find_package( OpenCV REQUIRED )

add_executable(flappy_bot src/flappy_bot.cpp)

set(LIBS ${OpenCV_LIBS})
target_link_libraries( flappy_bot ${LIBS} )
include(CPack)
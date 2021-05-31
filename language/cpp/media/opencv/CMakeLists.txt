cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )

add_executable( 00_video 00_video.cpp )
add_executable( 01_canny 01_canny.cpp )
add_executable( 02_template 02_template.cpp )
add_executable( 03_video 03_video.cpp )
add_executable( 04_thread 04_thread.cpp )

set(LIBS ${OpenCV_LIBS})


target_link_libraries( 00_video ${LIBS})
target_link_libraries( 01_canny ${LIBS})
target_link_libraries( 02_template ${LIBS})
target_link_libraries( 03_video ${LIBS})
target_link_libraries( 04_thread ${LIBS})
include(CPack)
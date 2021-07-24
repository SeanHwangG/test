cmake_minimum_required(VERSION 3.0)
project( DisplayImage )
find_package( OpenCV REQUIRED )

add_executable(main main.cpp)
set(LIBS ${OpenCV_LIBS})
target_link_libraries(main ${LIBS})
include(CPack)

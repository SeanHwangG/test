project("Hello")
cmake_minimum_required(VERSION 3.5)
 
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )
 
add_executable(Hello ${SOURCE_FILES})

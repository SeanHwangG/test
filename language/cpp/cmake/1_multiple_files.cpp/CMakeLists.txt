cmake_minimum_required(VERSION 3.0)
project(multiple_files)                         # Root CMAKE must have, set PROJECT_VERSION, PROJECT_NAME
add_definitions("-Wall -std=c++14")             # g++ -D option
add_executable(main main.cpp test.cpp)
cmake_minimum_required(VERSION 3.20)
project(advancedcpp_lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(advancedcpp_lab4
        src/main.cpp
 "src/timeit.h" "src/struct.cpp" "src/struct.h"    "src/thread_execution.h")

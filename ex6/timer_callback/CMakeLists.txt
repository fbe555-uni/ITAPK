cmake_minimum_required(VERSION 3.6)
project(timer_callback)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(timer_callback ${SOURCE_FILES})
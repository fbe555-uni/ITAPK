cmake_minimum_required(VERSION 3.6)
project(array_template)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MyArray.h)
add_executable(array_template ${SOURCE_FILES})
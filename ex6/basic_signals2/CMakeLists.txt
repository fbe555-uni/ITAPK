cmake_minimum_required(VERSION 3.6)
project(basic_signals2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(basic_signals2 ${SOURCE_FILES})
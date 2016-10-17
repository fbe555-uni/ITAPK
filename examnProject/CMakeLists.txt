cmake_minimum_required(VERSION 3.6)
project(CMS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/main.cpp src/trains.cpp src/trains.h src/station.cpp src/station.h src/cargo.h src/CMS.cpp src/CMS.h)
add_executable(CMS ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.6)
project(CMS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES src/main.cpp src/trains.cpp src/trains.hpp src/station.cpp src/station.hpp src/cargo.hpp src/CMS.cpp src/CMS.hpp src/SimulationController.cpp src/SimulationController.hpp)
add_executable(CMS ${SOURCE_FILES})
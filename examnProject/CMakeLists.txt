cmake_minimum_required(VERSION 2.8)
project(CMS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES
        src/main.cpp
        src/trains.cpp
        src/trains.hpp
        src/station.cpp
        src/station.hpp
        src/cargo.hpp
        src/CMS.cpp
        src/CMS.hpp
        src/SimulationController.cpp
        src/SimulationController.hpp
        src/ThreadSafeCout.hpp)
add_executable(CMS ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.6)
project(timer_callback)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Bindfunction.cpp
    Events.cpp
    Events.hpp
    Timer.cpp
    Timer.hpp)

find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



add_executable(timer_callback ${SOURCE_FILES})
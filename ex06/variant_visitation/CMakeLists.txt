cmake_minimum_required(VERSION 3.6)
project(variant_visitation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



set(SOURCE_FILES main.cpp)
add_executable(variant_visitation ${SOURCE_FILES})
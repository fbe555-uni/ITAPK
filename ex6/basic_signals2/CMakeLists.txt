cmake_minimum_required(VERSION 3.6)
project(basic_signals2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(basic_signals2 ${SOURCE_FILES})

find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

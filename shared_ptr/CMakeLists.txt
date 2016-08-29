cmake_minimum_required(VERSION 3.6)
project(shared_ptr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SharedPtr.cpp SharedPtr.h)
add_executable(shared_ptr ${SOURCE_FILES})
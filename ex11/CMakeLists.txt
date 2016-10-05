cmake_minimum_required(VERSION 3.6)
project(ex11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    MyAllocator/main.cpp
    MyAllocator/SmallObjectHeap.hpp
    MyAllocator/SmallObjectAllocator.hpp)

add_executable(ex11 ${SOURCE_FILES})
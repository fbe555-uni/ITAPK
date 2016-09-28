cmake_minimum_required(VERSION 3.6)
project(c11_select)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(NEW_BASIC_FACILITIES C++11Select/NewBasicFacilities/newalgo.cpp)
add_executable(newBasicFacilities ${NEW_BASIC_FACILITIES})

set(THREADING C++11Select/Threading/async_algo.cpp)
add_executable(threading ${THREADING})

cmake_minimum_required(VERSION 3.6)
project(stemachine_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SIMPLE_STATES_SRC Radio/SimpleStates/radio.cpp)
add_executable(simplestates ${SIMPLE_STATES_SRC})

set(MULTI_HIERARCH_SRC Radio/MultipleHierarchicalStates/radio.cpp)
add_executable(multiHierarch ${MULTI_HIERARCH_SRC})


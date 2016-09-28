cmake_minimum_required(VERSION 3.6)
project(stemachine_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SIMPLE_STATES_SRC Radio/SimpleStates/radio.cpp)
add_executable(simplestates ${SIMPLE_STATES_SRC})

set(MULTI_HIERARCH_SRC Radio/MultipleHierarchicalStates/radio.cpp)
add_executable(multiHierarch ${MULTI_HIERARCH_SRC})

set(GUARDED_TRANSITION_CUSTOM_REACTION Radio/GuardedTransInCustomReact/radio.cpp)
add_executable(guardedTransition ${GUARDED_TRANSITION_CUSTOM_REACTION})

set(INSTATE_STATEINFO_SRC Radio/InstateStateInformation/radio.cpp)
add_executable(instateStateinfo ${INSTATE_STATEINFO_SRC})

set(HISTORY_SRC Radio/History/radio.cpp)
add_executable(history ${HISTORY_SRC})
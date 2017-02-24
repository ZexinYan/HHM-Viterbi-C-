cmake_minimum_required(VERSION 3.5.2)
project(HMM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp __config.h forward.h viterbi.h example.h forwardAndBackward.h)
add_executable(HMM ${SOURCE_FILES})
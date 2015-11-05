cmake_minimum_required(VERSION 2.8)
project(read_cpu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(read_cpu ${SOURCE_FILES})
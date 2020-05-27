cmake_minimum_required(VERSION 3.15)
project(L3_Wilekowatkowosc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(L3 main.cpp)

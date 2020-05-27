cmake_minimum_required(VERSION 3.15)
project(L4_Sortowanie)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(Sortowanie main.cpp)
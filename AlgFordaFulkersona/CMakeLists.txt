cmake_minimum_required(VERSION 3.15)
project(AlgBelFor)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        AlgBelFor
        main.cpp
        FileLoader.h
        FileLoader.cpp
        Graph.h
        Graph.cpp
        Algorithm.h
        Algorithm.cpp
        Edge.h
        Edge.cpp
)
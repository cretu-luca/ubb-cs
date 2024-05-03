cmake_minimum_required(VERSION 3.26)
project(v2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(v2
        graph.cpp
        graph.h
        lab2.cpp
        lab3.cpp
        lab4.cpp
        menu.cpp)

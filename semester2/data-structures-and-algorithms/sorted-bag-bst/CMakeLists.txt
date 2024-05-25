cmake_minimum_required(VERSION 3.10)
project(SortedBagBST VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(SortedBagBST
        App.cpp
        ExtendedTest.cpp
        ShortTest.cpp
        SortedBag.cpp
        SortedBagIterator.cpp
)

target_include_directories(SortedBagBST PUBLIC "${PROJECT_BINARY_DIR}")

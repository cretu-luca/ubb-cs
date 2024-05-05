cmake_minimum_required(VERSION 3.26)
project(sorted_multimap_hashtable)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(sorted_multimap_hashtable
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)

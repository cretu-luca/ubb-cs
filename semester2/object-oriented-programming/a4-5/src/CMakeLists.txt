cmake_minimum_required(VERSION 3.26)

project(a4-5)

set(CMAKE_CXX_STANDARD 14)

add_executable(a4-5
            start.cpp
            exception.h
            userInterface/userInterface.cpp
            userInterface/userInterface.h
            repository/CSVRepository.h
            repository/HTMLRepository.h
            repository/repository.cpp
            repository/repository.h
            domain/movie.cpp
            domain/movie.h
            controller/controller.cpp
            controller/controller.h
            domain/movie.cpp)

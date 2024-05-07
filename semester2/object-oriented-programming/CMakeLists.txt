cmake_minimum_required(VERSION 3.28)
project(oop_a4_5_kpunkk_67)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/controller)
include_directories(src/domain)
include_directories(src/repository)
include_directories(src/UI)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6Widgets REQUIRED)

add_executable(oop_a4_5_kpunkk_67
        src/controller/controller.cpp
        src/controller/controller.h
        src/domain/movie.cpp
        src/domain/movie.h
        src/repository/CSVRepository.h
        src/repository/HTMLRepository.h
        src/repository/repository.cpp
        src/repository/repository.h
        src/UI/userInterface.cpp
        src/UI/userInterface.h
        src/exception.h
        src/start.cpp
        src/GUI/gui.cpp
        src/GUI/gui.h
        src/GUI/adminGUI.cpp
        src/GUI/userGUI.cpp
        src/GUI/userGUI.h
        src/GUI/adminGUI.h
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

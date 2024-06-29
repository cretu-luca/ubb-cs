cmake_minimum_required(VERSION 3.28)
project(practical_exam)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(practical_exam main.cpp
        domain.h
        repository.h
        service.h
        GUI.h
        courierwindow.cpp
        courierwindow.h
        courierwindow.ui
        companywindow.cpp
        companywindow.h
        companywindow.ui
        observer.h
        mapwindow.cpp
        mapwindow.h
        mapwindow.ui
)

target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
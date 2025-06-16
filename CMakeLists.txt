cmake_minimum_required(VERSION 3.10)
project(FreeEnergyPrinciple)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

set(SOURCES
    main.cpp
    Agent.cpp
    Environment.cpp
    MainWindow.cpp
)

set(HEADERS
    Agent.h
    Environment.h
    MainWindow.h
)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

add_executable(fep_simulation ${SOURCES} ${MOC_SOURCES})

target_link_libraries(fep_simulation Qt5::Widgets Qt5::Charts) 
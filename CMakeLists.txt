cmake_minimum_required(VERSION 4.2)

project(passman VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

add_executable( ${PROJECT_NAME} main.cpp manager.cpp)

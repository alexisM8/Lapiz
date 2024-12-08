cmake_minimum_required(VERSION 3.13.4)

project(Lapiz)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${FLAGS} -std=c++11")

add_executable(${PROJECT_NAME} main.cpp)

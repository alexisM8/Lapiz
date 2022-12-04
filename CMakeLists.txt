cmake_minimum_required(VERSION 3.13.4)

project(Lapiz)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${FLAGS} -std=c++14")

add_executable(${PROJECT_NAME} main.cpp)

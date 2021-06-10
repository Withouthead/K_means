cmake_minimum_required(VERSION 3.17)
project(K_means)

set(CMAKE_CXX_STANDARD 11)

include_directories(./eigen-3.4-rc1)
add_executable(K_means main.cpp)
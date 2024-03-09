cmake_minimum_required(VERSION 3.22)

include(CMakeEnv.txt)

project(myproject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("Building with CMake version: ${CMAKE_VERSION}")

add_subdirectory(./game/)
add_subdirectory(./wind/)

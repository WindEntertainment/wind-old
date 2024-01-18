cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_FLAGS "-std=c++23")
project(wind)

include_directories(./include/)

# modules 
add_subdirectory(./src/utils/)

# examples 
add_subdirectory(./examples/logger/)

# linking wind
add_library(${PROJECT_NAME} STATIC ./src/wind.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/utils/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-utils)
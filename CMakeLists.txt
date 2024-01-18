cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_FLAGS "-std=c++20")
project(wind)

include_directories(./include/)

# modules 
add_subdirectory(./src/logger/)

# examples 
add_subdirectory(./examples/logger/)

# linking wind
add_library(${PROJECT_NAME} STATIC ./src/wind.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/logger/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)
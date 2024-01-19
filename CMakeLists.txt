cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_FLAGS "-std=c++17")
project(wind)

message("Building with CMake version: ${CMAKE_VERSION}")

include_directories(./include/)

# modules 
add_subdirectory(./src/utils/)

# examples 
add_subdirectory(./examples/logger/)

# wind
add_library(${PROJECT_NAME} STATIC ./src/wind.cpp)

# internal 
target_include_directories(${PROJECT_NAME} PUBLIC ./src/utils/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-utils)

# external
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
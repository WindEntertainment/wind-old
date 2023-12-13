cmake_minimum_required(VERSION 3.22)

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)
SET (CMAKE_CXX_FLAGS "-std=c++20")

project(main)

add_subdirectory(./apps/logger)
add_subdirectory(./apps/cloudy)
add_subdirectory(./apps/asset-bundler)
add_subdirectory(./apps/resources)
add_subdirectory(./apps/system)
add_subdirectory(./apps/renderer)
add_subdirectory(./apps/breeze)

add_subdirectory(./apps/earth)
add_subdirectory(./apps/chaos)
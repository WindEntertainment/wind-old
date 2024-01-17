cmake_minimum_required(VERSION 3.22)

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)
SET (CMAKE_CXX_FLAGS "-std=c++20")

project(main)

add_subdirectory(./src/logger)
add_subdirectory(./src/cloudy)
add_subdirectory(./src/asset-bundler)
add_subdirectory(./src/resources)
add_subdirectory(./src/system)
add_subdirectory(./src/renderer)
add_subdirectory(./src/breeze)

add_subdirectory(./examples/scenes)
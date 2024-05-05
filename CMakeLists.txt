cmake_minimum_required(VERSION 3.22)

file(STRINGS ".env" ENV_VARS)
foreach(ENV_VAR ${ENV_VARS})
    string(REGEX MATCH "([^=]+)=([^=]*)" _ ${ENV_VAR})
    set(ENV{${CMAKE_MATCH_1}} "${CMAKE_MATCH_2}")
    # biba
    add_definitions(-D${CMAKE_MATCH_1}="${CMAKE_MATCH_2}")
    message(STATUS "Loaded environment variable: ${CMAKE_MATCH_1}=${CMAKE_MATCH_2}")
endforeach()

project(myproject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("Building with CMake version: ${CMAKE_VERSION}")

add_subdirectory(./editor/)
add_subdirectory(./game/)
add_subdirectory(./wind/)

include(cpack/cpack.cmake)

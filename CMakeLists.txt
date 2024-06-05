cmake_minimum_required(VERSION 3.22)

# Start read .env file
file(STRINGS ".env" ENV_VARS)
foreach(ENV_VAR ${ENV_VARS})
    string(REGEX MATCH "([^=]+)=([^=]*)" _ ${ENV_VAR})
    set(ENV{${CMAKE_MATCH_1}} "${CMAKE_MATCH_2}")
endforeach()
# End read .env file

project(myproject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("Building with CMake version: ${CMAKE_VERSION}")

# add_subdirectory(./editor/)
add_subdirectory(./wind/)
add_subdirectory(./game/)
add_subdirectory(./examples/)

include(cpack/cpack.cmake)

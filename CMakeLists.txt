cmake_minimum_required(VERSION 3.22)

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#   message("Testing enabled")
#   enable_testing()

#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
#     add_custom_target(coverage
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/coverage
#     COMMAND mkdir ${CMAKE_BINARY_DIR}/coverage
#     COMMAND game-tests
#     COMMAND wind-tests
#     COMMAND gcovr --root ${CMAKE_SOURCE_DIR} --exclude '.*/tests/.*' --exclude '.*/CMakeFiles/.*' --exclude '.*/build/.*' --html --html-details -o ${CMAKE_BINARY_DIR}/coverage/index.html
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#     COMMENT "Generating code coverage report..."
#   )
# endif()

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

add_subdirectory(./wind/)
add_subdirectory(./game/)
add_subdirectory(./examples/)
# add_subdirectory(./tests/)

include(cpack/cpack.cmake)

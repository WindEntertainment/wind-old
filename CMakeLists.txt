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

add_subdirectory(./wind/)
add_subdirectory(./game/)
add_subdirectory(./examples/)

############################################################
# Install
############################################################

# Binaries
install (TARGETS game DESTINATION bin)

# set(EXTERNAL_LIBRARIES glfw3)

# foreach(library ${EXTERNAL_LIBRARIES})
#     find_package(${library} REQUIRED)
#     target_link_libraries(game PRIVATE ${library}::${library})
#     endforeach()

# find_library(LIB )
# find_directory(GLFW3_LIBRARY "libglfw3.a")
install (DIRECTORY $ENV{ULTRALIGHT_PATH}/bin/ DESTINATION lib)

install (DIRECTORY game/res DESTINATION etc)

# Library
# Note: may not work on windows
# install (TARGETS glfw LIBRARY DESTINATION lib)

# Config
# install (FILES cmake-examples.conf
#     DESTINATION etc)

############################################################
# Create DEB
############################################################

# Tell CPack to generate a .deb package
set(CPACK_GENERATOR "Bundle")

# Set a Package Maintainer.
# This is required
set(CPACK_BUNDLE_PLIST ${CMAKE_SOURCE_DIR}/Info.plist)
set(CPACK_BUNDLE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns)
set(CPACK_BUNDLE_STARTUP_COMMAND ${CMAKE_BINARY_DIR}/game/game)
set(CPACK_BUNDLE_NAME "Dreich")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Dreich Inc")

# Set a Package Version
set(CPACK_PACKAGE_VERSION ${deb_example_VERSION})

# Include CPack
include(CPack)

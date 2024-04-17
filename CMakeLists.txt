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

add_subdirectory(./game/)
add_subdirectory(./wind/)

include(cpack/cpack.cmake)



#  with ETC
# install (DIRECTORY $ENV{DOTNET_INCLUDES}/ DESTINATION lib)
# install (DIRECTORY $ENV{ULTRALIGHT_PATH}/bin/ DESTINATION lib)

# set_target_properties(game PROPERTIES INSTALL_RPATH "@executable_path/../lib")
# install (DIRECTORY game/res DESTINATION etc)




# set(CMAKE_INSTALL_RPATH $LIBRARY_OUTPUT_PATH)

# set(EXTERNAL_LIBRARIES glfw3)

# foreach(library ${EXTERNAL_LIBRARIES})
#     find_package(${library} REQUIRED)
#     target_link_libraries(game PRIVATE ${library}::${library})
#     endforeach()

# find_library(LIB )
# find_directory(GLFW3_LIBRARY "libglfw3.a")

# Library
# Note: may not work on windows
# install (TARGETS glfw LIBRARY DESTINATION lib)

# Config
# install (FILES cmake-examples.conf
#     DESTINATION etc)

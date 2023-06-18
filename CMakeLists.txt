cmake_minimum_required(VERSION 3.22)

project(SoulDungeon)

add_executable(main 
    ./src/main.cpp
    ./src/application/Application.cpp
    ./src/application/window/Window.cpp
)

find_package(SDL2 CONFIG REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})
target_link_libraries(main 
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(glm CONFIG REQUIRED)
target_link_libraries(main PRIVATE glm::glm)

find_package(glog CONFIG REQUIRED)
target_link_libraries(main PRIVATE glog::glog)
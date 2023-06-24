cmake_minimum_required(VERSION 3.22)

project(SoulDungeon)

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

add_executable(main 
    ./src/main.cpp
    ./src/application/Application.cpp
    
    ./src/application/window/Window.cpp
    ./src/application/event-handlers/KeyEventHandler.cpp
    ./src/application/renderer/Renderer.cpp

    ./src/application/resources/ShaderLoader.cpp
    ./src/application/resources/IntLoader.cpp
    ./src/application/shader/Shader.cpp
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(main PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(main PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(main PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(glad CONFIG REQUIRED)
target_link_libraries(main PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(main PRIVATE glm::glm)

find_package(glog CONFIG REQUIRED)
target_link_libraries(main PRIVATE glog::glog)
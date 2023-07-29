cmake_minimum_required(VERSION 3.22)

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)

project(SoulDungeon)

add_executable(main 
    ./src/main.cpp
    ./src/application/Application.cpp
    
    ./src/application/window/Window.cpp
    ./src/application/event-handlers/KeyEventHandler.cpp
    ./src/application/canvas/Canvas.cpp
    ./src/application/renderer/Renderer.cpp

    ./src/application/resources/ShaderLoader.cpp
    ./src/application/resources/IntLoader.cpp
    ./src/application/shader/Shader.cpp
    ./src/application/world/World.cpp
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
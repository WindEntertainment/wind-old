project(wind)

add_library(${PROJECT_NAME} STATIC
    ./src/application.cpp

    ./src/window/window.cpp
    ./src/event-handlers/key_event_handler.cpp
    ./src/renderer/renderer.cpp
    ./src/mesh/mesh.cpp
    
    ./src/shader/shader.cpp

    ./src/entity/entity.cpp
    ./src/world/world.cpp
)

include_directories(../logger/)
include_directories(../asset-bundler/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
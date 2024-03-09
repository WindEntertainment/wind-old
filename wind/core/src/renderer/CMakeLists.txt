project(wind-renderer)

set(HEADERS
    ./include/renderer/camera.h
    ./include/renderer/mesh.h
    ./include/renderer/renderer.h
    ./include/renderer/shader.h
    ./include/renderer/texture.h
    ./include/renderer/particle.h
)

set(SOURCES
    ./src/mesh.cpp
    ./src/renderer.cpp
    ./src/shader.cpp
    ./src/texture.cpp
    ./src/particle.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

# internal depencencies
target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-resources)

# extrenal depencencies

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

#find_package(OpenGL REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

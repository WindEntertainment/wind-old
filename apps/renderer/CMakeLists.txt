project(renderer)

add_library(${PROJECT_NAME} STATIC
    ./renderer/renderer.h
    ./renderer/renderer.cpp

    ./renderer/texture.h
    ./renderer/texture.cpp

    ./renderer/shader.h
    ./renderer/shader.cpp

    ./renderer/mesh.h
    ./renderer/mesh.cpp
    
    ./renderer/utils.h

    ./renderer/camera.h
)

include_directories(../renderer/)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

#find_package(OpenGL REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

#find_package(glad CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
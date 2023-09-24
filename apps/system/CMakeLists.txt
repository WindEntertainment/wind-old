project(system)

add_library(${PROJECT_NAME} STATIC
    ./system/application.h
    ./system/application.cpp

    ./system/window.h
    ./system/window.cpp

    ./system/events/mouse.h
    ./system/events/mouse.cpp
    
    ./system/events/keyboard.h
    ./system/events/keyboard.cpp
    
    ./system/utils.h
    ./system/utils.cpp
)

include_directories(../renderer/)
include_directories(../logger/)
include_directories(../asset-bundler/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
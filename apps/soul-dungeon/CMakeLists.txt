project(soul-dungeon)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
)

include_directories(../logger/)
include_directories(../asset-bundler/)
include_directories(../wind/src/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)
target_link_libraries(${PROJECT_NAME} PRIVATE wind)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
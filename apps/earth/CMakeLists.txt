project(earth)

add_library(${PROJECT_NAME} STATIC
    ./earth/earth.h
    ./earth/earth.cpp

    ./earth/main.cpp
)

## internal

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

include_directories(../asset-bundler/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)

# external

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
project(resources)

add_library(${PROJECT_NAME} STATIC
    ./resources/resource_manager.h
    ./resources/resource_manager.cpp
    
    ./resources/getters/asset.h
    
    ./resources/getters/texture.h
    ./resources/getters/texture.cpp
)

include_directories(../resources/)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

include_directories(../asset-bundler/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)

include_directories(../renderer/)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
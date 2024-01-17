project(resources)

add_library(${PROJECT_NAME} STATIC
    ./resources/resource_manager.h
    ./resources/resource_manager.cpp
    
    ./resources/getters/asset.h
    
    ./resources/getters/texture.h
    ./resources/getters/texture.cpp

    ./resources/getters/shader.h
    ./resources/getters/shader.cpp

    ./resources/getters/mesh.h
    ./resources/getters/mesh.cpp

    ./resources/getters/prefab.h
    ./resources/getters/prefab.cpp
)

include_directories(../resources/)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

include_directories(../asset-bundler/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)

include_directories(../renderer/)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

include_directories(../breeze/)
target_link_libraries(${PROJECT_NAME} PRIVATE breeze)

include_directories(../system/)
target_link_libraries(${PROJECT_NAME} PRIVATE system)

include_directories(../cloudy/)
target_link_libraries(${PROJECT_NAME} PRIVATE cloudy)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
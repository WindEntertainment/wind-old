project(breeze)

add_library(${PROJECT_NAME} STATIC
    ./breeze/breeze.h
    ./breeze/breeze.cpp

    # systems
    ./breeze/systems/system.h

    ./breeze/systems/render.h
    ./breeze/systems/render.cpp

    # components
    ./breeze/components/transform.h
    ./breeze/components/renderable.h

    # prefab
    ./breeze/prefab/prefab.h
    ./breeze/prefab/prefab.cpp
    
    ./breeze/prefab/component_registry.h
    ./breeze/prefab/component_registry.cpp
)

include_directories(../breeze/)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

include_directories(../asset-bundler/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)

include_directories(../renderer/)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

include_directories(../resources/)
target_link_libraries(${PROJECT_NAME} PRIVATE resources)

include_directories(../cloudy/)
target_link_libraries(${PROJECT_NAME} PRIVATE cloudy)

include_directories(../system/)
target_link_libraries(${PROJECT_NAME} PRIVATE system)

##

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE EnTT::EnTT)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
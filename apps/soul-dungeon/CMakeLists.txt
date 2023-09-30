project(soul-dungeon)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    
    ./src/camera_controll.h
    ./src/camera_controll.cpp

    ./src/level.h
    ./src/level_one.h
    ./src/level_one.cpp

    ./src/game.h
    ./src/game.cpp
    
    ./src/utils.h

    ./src/transform.h
    ./src/mesh.h

    ./src/system.h
    
    ./src/render.h
    ./src/render.cpp
)

## internal

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

include_directories(../asset-bundler/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)

include_directories(../renderer/)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

include_directories(../system/)
target_link_libraries(${PROJECT_NAME} PRIVATE system)

##

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE EnTT::EnTT)
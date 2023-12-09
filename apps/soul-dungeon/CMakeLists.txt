project(soul-dungeon)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    
    ./src/systems/camera_controll.h
    ./src/systems/camera_controll.cpp
 
    ./src/systems/render.h
    ./src/systems/render.cpp


    ./src/level.h
    ./src/level_one.h
    ./src/level_one.cpp

    ./src/game.h
    ./src/game.cpp
    
    ./src/utils.h
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

include_directories(../resources/)
target_link_libraries(${PROJECT_NAME} PRIVATE resources)

include_directories(../std-game/)
target_link_libraries(${PROJECT_NAME} PRIVATE std-game)

include_directories(../cloudy/)
target_link_libraries(${PROJECT_NAME} PRIVATE cloudy)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
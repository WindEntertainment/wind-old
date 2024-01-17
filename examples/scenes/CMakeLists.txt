project(chaos)

add_executable(${PROJECT_NAME}
    ./chaos/main.cpp
    
    ./chaos/systems/camera_controll.h
    ./chaos/systems/camera_controll.cpp
 
    ./chaos/game.h
    ./chaos/game.cpp
    
    ./chaos/utils.h
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

include_directories(../breeze/)
target_link_libraries(${PROJECT_NAME} PRIVATE breeze)

include_directories(../cloudy/)
target_link_libraries(${PROJECT_NAME} PRIVATE cloudy)

include_directories(../earth/)
target_link_libraries(${PROJECT_NAME} PRIVATE earth)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
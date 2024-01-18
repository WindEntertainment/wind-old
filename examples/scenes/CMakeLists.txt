project(chaos)

add_executable(${PROJECT_NAME}
    ./chaos/main.cpp
    
    ./chaos/systems/camera_controll.h
    ./chaos/systems/camera_controll.cpp
 
    ./chaos/game.h
    ./chaos/game.cpp
    
    ./chaos/utils.h
)


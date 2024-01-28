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

#include_directories(../renderer/)
#target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

# find_package(glad CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
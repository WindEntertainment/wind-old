project(system)

set(SOURCES
    ./system/application.cpp
    ./system/window.cpp
    
    ./system/events/mouse.cpp
    ./system/events/keyboard.cpp
    
    ./system/utils.cpp
)

add_library(${PROJECT_NAME} STATIC
    ./system/application.h
    ./system/window.h

    ./system/events/mouse.h
    ./system/events/keyboard.h    
    
    ./system/utils.h
)

include_directories(./include)

#include_directories(../renderer/)
#target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

# find_package(glad CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
project(wind-window)

set(SOURCES
    ./src/window.cpp
    
    ./src/events/mouse.cpp
    ./src/events/keyboard.cpp
)

set(HEADERS
    ./include/window/window.h

    ./include/window/events/mouse.h
    ./include/window/events/keyboard.h    
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

# internal 

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)

# external 

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

#include_directories(../renderer/)
#target_link_libraries(${PROJECT_NAME} PRIVATE renderer)
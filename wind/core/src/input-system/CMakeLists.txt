project(wind-input-system)

set(HEADERS
    ./include/input-system/input-system.h
    ./include/input-system/mouse-context.h
    ./include/input-system/keyboard-context.h
    ./include/input-system/context.h
    ./include/input-system/keys.h
    ./include/input-system/trigger.h
)

set(SOURCES
    ./src/input-system.cpp
    ./src/mouse-context.cpp
    ./src/keyboard-context.cpp
    ./src/context.cpp
    ./src/keys.cpp
    ./src/trigger.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

# internal depencencies

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)

# extrenal depencencies

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)

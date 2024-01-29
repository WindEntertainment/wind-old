project(window)

set(SOURCES
    ./src/application.cpp
    ./src/window.cpp
    
    ./src/events/mouse.cpp
    ./src/events/keyboard.cpp
    
    ./src/utils.cpp
)

set(HEADERS
    ./include/application.h
    ./include/window.h

    ./include/events/mouse.h
    ./include/events/keyboard.h    

    ./include/utils.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

include_directories(./include)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

#find_package(glfw3 CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

#include_directories(../renderer/)
#target_link_libraries(${PROJECT_NAME} PRIVATE renderer)
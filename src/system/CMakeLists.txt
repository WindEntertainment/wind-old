project(system)

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

#include_directories(../renderer/)
#target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

# find_package(glad CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
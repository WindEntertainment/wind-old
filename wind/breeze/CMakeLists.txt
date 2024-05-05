project(wind-breeze)

set(HEADERS
    ./include/breeze/breeze.hpp

)

set(SOURCES
    ./src/breeze.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

# internal depencencies

target_link_libraries(${PROJECT_NAME} PUBLIC wind-core)
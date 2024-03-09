project(wind-resources)

set(HEADERS
    ./include/resources/default.h
)

set(SOURCES
    ./src/default.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

# internal depencencies
target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)

# internal depencencies
target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)
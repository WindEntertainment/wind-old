project(wind-utils)

set(HEADERS
    ./include/utils/ext_filesystem.h
    ./include/utils/ext_string.h
    ./include/utils/includes.h
    ./include/utils/math.h
    ./include/utils/utils.h
)

set(SOURCES
    ./src/ext_filesystem.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

include_directories(./include/)

# external
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
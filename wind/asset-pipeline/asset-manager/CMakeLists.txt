project(wind-asset-manager)

set(HEADERS
    ./include/asset-manager/asset-manager.hpp
)
set(SOURCES
    ./src/asset-manager.cpp
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

target_link_libraries(${PROJECT_NAME} PUBLIC wind-asset-pipes)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-utils)

find_package(pugixml REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml::pugixml)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(ZLIB REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ZLIB::ZLIB)

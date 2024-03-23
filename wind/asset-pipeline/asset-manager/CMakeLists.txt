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
target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)

find_package(pugixml REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml::pugixml)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(Stb REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
project(asset-pipeline)

set(SOURCES
    ./src/main.cpp
    ./src/asset-pipeline.cpp
)

set(HEADERS
    ./include/asset-pipeline/asset-pipeline.h
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

# internal
target_link_libraries(${PROJECT_NAME} PRIVATE wind)

# external
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)


# find_package(glm CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# find_package(OpenSSL REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# find_package(tinyxml2 CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2::tinyxml2)

# find_package(assimp CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)

# find_package(Stb REQUIRED)
# target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
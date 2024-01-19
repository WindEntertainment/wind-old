project(logger-example)

set(SOURCES 
    ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# internal 
target_link_libraries(${PROJECT_NAME} PRIVATE wind)

# external
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)
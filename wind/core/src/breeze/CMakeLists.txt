project(wind-breeze)

set(SOURCES
./breeze/breeze.cpp
)

set(HEADERS
./breeze/breeze.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-resources)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)

# external

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
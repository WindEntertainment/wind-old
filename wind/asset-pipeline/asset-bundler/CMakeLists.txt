project(wind-asset-bundler)

include(../pipes/CMakeLists.txt)

set(HEADERS
    ./include/asset-bundler/asset-bundler.hpp
)

set(SOURCES
    ./src/main.cpp
    ./src/asset-bundler.cpp
    ./src/preprocessing.cpp
) 

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)

target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)
target_include_directories(${PROJECT_NAME} PUBLIC ${PIPES_INCLUDE_DIR})

find_package(cxxopts REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts::cxxopts)
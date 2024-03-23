project(wind-asset-bundler)

set(HEADERS
    ./include/asset-bundler/asset-bundler.hpp
)

set(SOURCES
    ./src/main.cpp
    ./src/asset-bundler.cpp
    ./src/preprocessing.cpp
) 

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)

target_link_libraries(${PROJECT_NAME} PUBLIC wind-asset-pipes)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)

find_package(stb REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE stb::stb)

find_package(ZLIB REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ZLIB::ZLIB)

find_package(cxxopts REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts::cxxopts)

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)

find_package(pugixml REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml::pugixml)
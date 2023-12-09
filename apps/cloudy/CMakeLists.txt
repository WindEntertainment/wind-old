project(cloudy)

add_library(${PROJECT_NAME} STATIC
    ./cloudy/xml.cpp

    ./cloudy/document.cpp

    ./cloudy/value.cpp
    ./cloudy/container.cpp
)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

find_package(tinyxml2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2::tinyxml2)

include_directories(../cloudy/)
project(cloudy)

add_library(${PROJECT_NAME} STATIC
    ./cloudy/xml.h
    ./cloudy/xml.cpp

    ./cloudy/document.h
    ./cloudy/document.cpp

    ./cloudy/object.h
    ./cloudy/value.cpp
    ./cloudy/container.cpp

    ./cloudy/utils.h
)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

find_package(tinyxml2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2::tinyxml2)

include_directories(../cloudy/)
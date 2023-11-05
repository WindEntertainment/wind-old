project(dom)

add_library(${PROJECT_NAME} STATIC
    ./dom/xml.h
    ./dom/xml.cpp

    ./dom/document.h
    ./dom/document.cpp

    ./dom/object.h
    ./dom/object.cpp

    ./dom/utils.h
)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

find_package(tinyxml2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2::tinyxml2)

include_directories(../dom/)
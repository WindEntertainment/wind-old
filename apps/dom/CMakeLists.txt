project(dom)

add_library(${PROJECT_NAME} STATIC
    ./dom/document.h
    ./dom/document.cpp

    ./dom/object.h
    ./dom/object.cpp

    ./dom/utils.h
)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

include_directories(../dom/)
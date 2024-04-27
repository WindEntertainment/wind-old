project(wind)

add_subdirectory(./core/)
add_subdirectory(./examples/)
add_subdirectory(./ultralight/)
add_subdirectory(./asset-pipeline/)

include(./entry/entry.cmake)
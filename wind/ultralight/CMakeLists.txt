project(wind-ultralight)

set(ULTRALIGHT_INCLUDE_DIR "$ENV{ULTRALIGHT_PATH}/include")
set(ULTRALIGHT_BINARY_DIR "$ENV{ULTRALIGHT_PATH}/bin")
set(ULTRALIGHT_LIBRARY_DIR "$ENV{ULTRALIGHT_PATH}/lib")
set(ULTRALIGHT_INSPECTOR_DIR "$ENV{ULTRALIGHT_PATH}/inspector")
set(ULTRALIGHT_RESOURCES_DIR "$ENV{ULTRALIGHT_PATH}/resources")

set(HEADERS
    ./include/wind-ultralight/ultralight.h
    ./include/wind-ultralight/filesystem.hpp
)

set(SOURCES
    ./src/ultralight.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/renderer/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/input-system/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)

target_link_libraries(${PROJECT_NAME} PRIVATE wind-asset-manager)

# WIN FIX
target_include_directories(${PROJECT_NAME} PUBLIC "${ULTRALIGHT_INCLUDE_DIR}")
# target_link_directories(${PROJECT_NAME} PUBLIC "${ULTRALIGHT_BINARY_DIR}")
# message(${ULTRALIGHT_BINARY_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC "${ULTRALIGHT_LIBRARY_DIR}")
message(${ULTRALIGHT_LIBRARY_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC UltralightCore AppCore Ultralight WebCore)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

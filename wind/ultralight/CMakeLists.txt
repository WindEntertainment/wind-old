project(wind-ultralight)

set(ULTRALIGHT_INCLUDE_DIR "$ENV{ULTRALIGHT_PATH}/include")
set(ULTRALIGHT_BINARY_DIR "$ENV{ULTRALIGHT_PATH}/bin")
set(ULTRALIGHT_LIBRARY_DIR "$ENV{ULTRALIGHT_PATH}/lib")
set(ULTRALIGHT_INSPECTOR_DIR "$ENV{ULTRALIGHT_PATH}/inspector")
set(ULTRALIGHT_RESOURCES_DIR "$ENV{ULTRALIGHT_PATH}/resources")

set(HEADERS
    ./include/wind-ultralight/js-core-utils.hpp

    ./include/wind-ultralight/ultralight.h
    ./include/wind-ultralight/filesystem.hpp
    ./include/wind-ultralight/load-logger.h
    ./include/wind-ultralight/network-logger.h
    ./include/wind-ultralight/view-logger.h
)

set(SOURCES
    ./src/js-core-utils.cpp

    ./src/ultralight.cpp
    ./src/load-logger.cpp
    ./src/network-logger.cpp
    ./src/view-logger.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/renderer/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/input-system/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)

target_link_libraries(${PROJECT_NAME} PRIVATE wind-asset-manager)

target_include_directories(${PROJECT_NAME} PUBLIC "${ULTRALIGHT_INCLUDE_DIR}")

if (WIN32)
  target_link_directories(${PROJECT_NAME} PUBLIC "${ULTRALIGHT_LIBRARY_DIR}")
else()
  target_link_directories(${PROJECT_NAME} PUBLIC "${ULTRALIGHT_BINARY_DIR}")
endif()


target_link_libraries(${PROJECT_NAME} PUBLIC UltralightCore AppCore Ultralight WebCore)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

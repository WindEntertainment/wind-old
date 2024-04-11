project(game)

set(SOURCES
    ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-ultralight)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-asset-manager)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-input-system)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-script-system)


include_directories("$ENV{DOTNET_INCLUDES}")
target_link_libraries(${PROJECT_NAME} PUBLIC "$ENV{DOTNET_INCLUDES}/libnethost.a")

set(ASSETS_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/")
set(ULTRALIGHT_RESOURCES_DIR "$ENV{ULTRALIGHT_PATH}/resources")

# Copy assets to assets directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/assets.bundle" "${ASSETS_PATH}")

project(game)

set(SOURCES
    ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
find_package(stb REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE stb::stb)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-ultralight)

#  Ultralight staff
# if (APPLE)
#   set(ASSETS_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources/assets")
# else ()
# set(ASSETS_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")
# endif ()

set(ASSETS_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/")
set(ULTRALIGHT_RESOURCES_DIR "$ENV{ULTRALIGHT_PATH}/resources")

# Copy assets to assets directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/assets.bundle" "${ASSETS_PATH}")
# Copy resources to assets directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_RESOURCES_DIR}" "${ASSETS_PATH}/resources")

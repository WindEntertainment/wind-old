project(editor)

set(SOURCES
    ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-ultralight)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-asset-manager)

set(ASSETS_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res" "${ASSETS_PATH}")

project(game)

set(SOURCES
  ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-ultralight)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-asset-manager)

set(ASSETS_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res")

file(GLOB_RECURSE RES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/res/*")

add_custom_target(copy_resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res "${ASSETS_PATH}"
  COMMENT "Copying resources folder before build"
  VERBATIM
)

add_dependencies(${PROJECT_NAME} copy_resources)

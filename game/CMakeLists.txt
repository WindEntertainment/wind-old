project(game)

set(HEADERS
  ./app/include/game/worlds/game-world.hpp
  ./app/include/game/utils.hpp
)

set(SOURCES
    ./app/src/main.cpp
    ./app/src/worlds/game-world.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
include_directories(./app/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-ultralight)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-asset-manager)

set(ASSETS_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res")

# Copy assets to assets directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res" "${ASSETS_PATH}")

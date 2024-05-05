project(game)

set(SOURCES
  ./src/main.cpp
)

file(GLOB SOURCES "./src/**.*")
file(GLOB HEADERS "./include/**.*")

# Add executable and link libraries
# add_executable(YourProjectExecutable main.cpp ${YourProject_INCLUDES})

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

# file(GLOB_RECURSE SCHEMA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/schemas/*")

# add_custom_target(generate_types
#   COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/../wm/wm run generate-types -p game"
#   COMMENT "Generating types from schemas"
#   VERBATIM
# )

# add_dependencies(${PROJECT_NAME} generate_types)

# set(GENERATED_HPP_DIR "./include/game/generated")

# # Add the generated .hpp files to the project
# file(GLOB GENERATED_HPP_FILES "./include/game/generated/*")

# # Include the generated .hpp files in your project
# include_directories(${GENERATED_HPP_DIR})

# target_sources(${PROJECT_NAME}  PRIVATE ${GENERATED_HPP_FILES})

set(SCHEMAS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/schemas)

# add_custom_command(
#     OUTPUT "${CMAKE_BINARY_DIR}/*.hpp"
#     COMMAND wm run generate-types -p game
#     DEPENDS "${SCHEMAS_PATH}/*.json"
# )

add_custom_target(generate_types
  COMMAND wm run generate-types -p game
  COMMENT "Generating types from schemas"
  VERBATIM
)

add_dependencies(${PROJECT_NAME} generate_types)

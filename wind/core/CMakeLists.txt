project(wind-core)

# modules
add_subdirectory(./src/utils/)
add_subdirectory(./src/window/)
add_subdirectory(./src/breeze/)
add_subdirectory(./src/renderer/)
add_subdirectory(./src/resources/)
add_subdirectory(./src/input-system/)
add_subdirectory(./src/script-system/)

# wind
add_library(${PROJECT_NAME} STATIC ./include/wind.h ./src/wind.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-window)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-breeze)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-resources)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-script-system)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-asset-manager)
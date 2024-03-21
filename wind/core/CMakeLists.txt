project(wind-core)

# modules
add_subdirectory(./src/utils/)
add_subdirectory(./src/window/)
add_subdirectory(./src/renderer/)
add_subdirectory(./src/resources/)
add_subdirectory(./src/input-system/)
add_subdirectory(./src/script-system/)

# wind
add_library(${PROJECT_NAME} STATIC ./include/wind.h ./src/wind.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/utils/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/window/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-window)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/renderer/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/resources/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-resources)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/input-system/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/script-system/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-script-system)

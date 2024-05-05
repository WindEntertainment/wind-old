project(wind-core)

# modules
add_subdirectory(./utils/)
add_subdirectory(./window/)
add_subdirectory(./renderer/)
add_subdirectory(./resources/)
add_subdirectory(./input-system/)
add_subdirectory(./asset-pipeline/)

# wind
add_library(${PROJECT_NAME} SHARED core.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-window)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-renderer)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-resources)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-input-system)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-asset-manager)
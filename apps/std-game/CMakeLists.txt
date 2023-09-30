project(std-game)

add_library(${PROJECT_NAME} STATIC
    ./std-game/system.h

    ./std-game/transform.h
    ./std-game/mesh.h
)

include_directories(../resources/)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

include_directories(../asset-bundler/)
target_link_libraries(${PROJECT_NAME} PRIVATE asset-bundler)

include_directories(../renderer/)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

##

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE EnTT::EnTT)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
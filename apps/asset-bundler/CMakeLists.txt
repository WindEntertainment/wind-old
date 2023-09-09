project(asset-bundler)

add_library(${PROJECT_NAME} STATIC
    ./asset-bundler/asset_bundler.h
    ./asset-bundler/asset_bundler.cpp

    ./asset-bundler/iloader.h
    ./asset-bundler/iserializable.h
)

include_directories(../asset-bundler/)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)
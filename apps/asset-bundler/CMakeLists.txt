project(asset-bundler)

add_library(${PROJECT_NAME} STATIC
    ./asset-bundler/utils.h
    ./asset-bundler/utils.cpp
        
    ./asset-bundler/asset_bundler.h
    ./asset-bundler/asset_bundler.cpp

    ./asset-bundler/loaders/iloader.h
    ./asset-bundler/loaders/obj_loader.h
    ./asset-bundler/loaders/obj_loader.cpp
    ./asset-bundler/loaders/shader_loader.h
    ./asset-bundler/loaders/shader_loader.cpp
    ./asset-bundler/loaders/image_loader.h
    ./asset-bundler/loaders/image_loader.cpp

    ./asset-bundler/objects/iserializable.h
    ./asset-bundler/objects/mesh.h
    ./asset-bundler/objects/mesh.cpp
    ./asset-bundler/objects/shader.h
    ./asset-bundler/objects/shader.cpp
    ./asset-bundler/objects/image.h
    ./asset-bundler/objects/image.cpp

    ./asset-bundler/bundle.h
    ./asset-bundler/bundle.cpp
)

include_directories(../asset-bundler/)

include_directories(../logger/)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

find_package(tinyxml2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2::tinyxml2)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)

find_package(Stb REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
project(wind-asset)

set(SOURCES_PIPELINE
    ./src/main.cpp
    ./src/asset-pipeline.cpp
    ./src/pipes-register.cpp
    ./src/preprocessing.cpp

    # pipes 
    ./src/pipes/default-pipe.cpp
    ./src/pipes/img-pipe.cpp
    ./src/pipes/shader-pipe.cpp
)

set(HEADERS_PIPELINE
    ./include/asset-pipeline/asset-pipeline.h
    ./include/asset-pipeline/pipes-register.h

    # pipes 
    ./include/asset-pipeline/pipes/pipe.h
    ./include/asset-pipeline/pipes/default-pipe.h
    ./include/asset-pipeline/pipes/img-pipe.h
    ./include/asset-pipeline/pipes/shader-pipe.h

    # assets
    ./include/asset-pipeline/asset-manager.h
    ./include/asset-pipeline/assets/asset.h
    ./include/asset-pipeline/assets/default.h

)

add_executable(${PROJECT_NAME} ${HEADERS_PIPELINE} ${SOURCES_PIPELINE})
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)

set(SOURCES_MANAGER
    ./src/asset-manager.cpp
)

set(HEADERS_MANAGER
    ./include/asset-pipeline/asset-manager.h
)

add_library(wind-asset-manager ${SOURCES_MANAGER} ${HEADERS_MANAGER})
target_include_directories(wind-asset-manager PUBLIC ./include/)

find_package(spdlog REQUIRED)
target_link_libraries(wind-asset-manager PUBLIC spdlog::spdlog)
target_link_libraries(wind-asset-manager PUBLIC wind-core)

find_package(yaml-cpp REQUIRED)
target_link_libraries(wind-asset-manager PUBLIC yaml-cpp::yaml-cpp)

# includes
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

# internal
target_link_libraries(${PROJECT_NAME} PRIVATE wind-core)

# external
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)

find_package(assimp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)

find_package(stb REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE stb::stb)

find_package(pugixml REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml::pugixml)

find_package(cxxopts REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts::cxxopts)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# find_package(OpenSSL REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# find_package(tinyxml2 CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2::tinyxml2)

# find_package(Stb REQUIRED)
# target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
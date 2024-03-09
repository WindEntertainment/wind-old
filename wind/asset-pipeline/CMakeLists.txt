project(windasset)

set(SOURCES
    ./src/main.cpp
    ./src/asset-pipeline.cpp
    ./src/pipes-register.cpp

    # pipes 
    ./src/pipes/default-pipe.cpp
    ./src/pipes/content-3d-pipe.cpp
    ./src/pipes/img-pipe.cpp
    ./src/pipes/shader-pipe.cpp
)

set(HEADERS
    ./include/asset-pipeline/asset-pipeline.h
    ./include/asset-pipeline/pipes-register.h

    ./include/asset-pipeline/pipe.h

    # pipes 
    ./include/asset-pipeline/pipes/default-pipe.h
    ./include/asset-pipeline/pipes/content-3d-pipe.h
    ./include/asset-pipeline/pipes/img-pipe.h
    ./include/asset-pipeline/pipes/shader-pipe.h

)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)

# includes

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

# internal
target_link_libraries(${PROJECT_NAME} PRIVATE wind)

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
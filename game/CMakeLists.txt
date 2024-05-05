project(game)

set(HEADERS
  ./app/include/game/worlds/game-world.hpp
  ./app/include/game/utils.hpp
)

set(SOURCES
    ./app/src/main.cpp
    ./app/src/worlds/game-world.cpp
)


add_wind_game(${PROJECT_NAME} "main;resources" ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ./app/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE wind-breeze)
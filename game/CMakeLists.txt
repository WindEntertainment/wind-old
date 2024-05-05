project(game)

set(HEADERS
  ./app/include/game/systems/move-system.hpp
  ./app/include/game/systems/render-system.hpp
  ./app/include/game/worlds.hpp
  ./app/include/game/utils.hpp
)

set(SOURCES
    ./app/src/main.cpp
    ./app/src/worlds/game-world.cpp
    ./app/src/systems/render-system.cpp
    ./app/src/systems/move-system.cpp
)


add_wind_game(${PROJECT_NAME} "main;resources" ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ./app/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE wind-breeze)
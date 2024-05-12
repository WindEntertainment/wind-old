project(tic-tac-toe)

set(HEADERS
  ./app/include/game/components/map.hpp
  ./app/include/game/components/transform.hpp
  ./app/include/game/components/renderable.hpp
  ./app/include/game/components/map.hpp

  ./app/include/game/systems/render-system.hpp
  ./app/include/game/systems/player-system.hpp

  ./app/include/game/worlds.hpp
  ./app/include/game/utils.hpp
)

set(SOURCES
  ./app/src/systems/render-system.cpp
  ./app/src/systems/player-system.cpp

  ./app/src/worlds/game-world.cpp
  ./app/src/main.cpp
)

add_wind_game(${PROJECT_NAME} "main;resources" ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ./app/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE wind-breeze)
#include <breeze/breeze.hpp>

#include "game/components/game-state.hpp"
#include "game/components/map.hpp"
#include "game/components/renderable.hpp"
#include "game/components/transform.hpp"

#include "game/systems/tictactoe-system.hpp"

namespace game {

inline bool stillHaveEmpty(Map& map) {
  for (int i = 0; i < MAP_WIDTH; ++i)
    for (int j = 0; j < MAP_HEIGHT; ++j)
      if (map.map[i][j] == Sign::EMPTY)
        return true;
  return false;
}

inline Sign findWinner(Map& map) {
  for (const auto& row : map.map)
    if (row[0] != EMPTY && row[0] == row[1] && row[0] == row[2])
      return row[0];

  for (int col = 0; col < 3; ++col)
    if (map.map[0][col] != EMPTY && map.map[0][col] == map.map[1][col] && map.map[0][col] == map.map[2][col])
      return map.map[0][col];

  if (map.map[0][0] != EMPTY && map.map[0][0] == map.map[1][1] && map.map[0][0] == map.map[2][2])
    return map.map[0][0];

  if (map.map[0][2] != EMPTY && map.map[0][2] == map.map[1][1] && map.map[0][2] == map.map[2][0])
    return map.map[0][2];

  return Sign::EMPTY;
}

inline void clearMap(Map& map, wind::World& world) {
  for (int i = 0; i < MAP_WIDTH; ++i)
    for (int j = 0; j < MAP_HEIGHT; ++j) {
      map.map[i][j] = Sign::EMPTY;
      world.getComponent<Renderable>(map.cells[i][j]).texture = nullptr;
    }
}

void TicTacToeSystem::update(wind::World& world) {
  auto& map = world.getComponent<Map>(gameState);

  auto winner = findWinner(map);
  if (winner != Sign::EMPTY || (winner == Sign::EMPTY && !stillHaveEmpty(map))) {
    clearMap(map, world);

    auto& state = world.getComponent<GameState>(gameState);
    state.stepBy = StepBy::PLAYER;
  }
}

} // namespace game
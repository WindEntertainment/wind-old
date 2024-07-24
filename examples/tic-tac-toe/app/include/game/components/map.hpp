#pragma once
#include "game/utils.hpp"

namespace game {

struct Map {
  Sign map[MAP_WIDTH][MAP_HEIGHT];
  Entity cells[MAP_WIDTH][MAP_HEIGHT];

  Map() {
    for (int i = 0; i < MAP_WIDTH; i++)
      for (int j = 0; j < MAP_HEIGHT; j++)
        map[i][j] = Sign::EMPTY;
  }
};

} // namespace game
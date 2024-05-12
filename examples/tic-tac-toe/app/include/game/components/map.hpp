#pragma once
#include "game/utils.hpp"

namespace game {

struct Map {
  Sign map[MAP_WIDTH][MAP_HEIGHT];
  Entity cells[MAP_WIDTH][MAP_HEIGHT];
};

} // namespace game
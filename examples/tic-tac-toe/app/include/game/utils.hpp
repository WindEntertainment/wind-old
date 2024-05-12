#pragma once
#include <renderer/renderer.hpp>

#include <asset-manager/asset-manager.hpp>
#include <breeze/breeze.hpp>
#include <input-system/input-system.h>
#include <renderer/assets.hpp>
#include <utils/utils.h>
#include <window/window.h>

using namespace wind;
// using namespace wind::assets;

namespace game {

enum Sign {
  EMPTY,
  TOES,
  CROSSES
};

static const int MAP_WIDTH = 3;
static const int MAP_HEIGHT = 3;
static const int CELL_SIZE = 168;

} // namespace game

using namespace game;
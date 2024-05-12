#pragma once
#include <glad/glad.h>

#include <asset-manager/asset-manager.hpp>
#include <breeze/breeze.hpp>
#include <input-system/input-system.h>
#include <renderer/assets.hpp>
#include <renderer/renderer.hpp>
#include <utils/utils.h>
#include <window/window.h>

using namespace wind;
using namespace wind::assets;

namespace game {

enum Sign {
  EMPTY,
  TOES,
  CROSSES
};

}

using namespace game;
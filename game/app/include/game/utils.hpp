#pragma once
#include <glad/glad.h>

#include <asset-manager/asset-manager.hpp>
#include <breeze/breeze.hpp>
#include <input-system/input-system.h>
#include <renderer/renderer.hpp>
#include <utils/utils.h>
#include <window/window.h>

using namespace wind;
using namespace wind::assets;

namespace game {}
using namespace game;

template <>
Texture* AssetManager::getAsset(const char* _key);
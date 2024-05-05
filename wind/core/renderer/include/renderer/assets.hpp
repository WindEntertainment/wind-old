#include <asset-manager/asset-manager.hpp>
#include <renderer/texture.hpp>

namespace wind {
template <>
Texture* AssetManager::getAsset(const char* _key);
}
#include <asset-manager/asset-manager.hpp>
#include <renderer/texture.hpp>

namespace wind {
template <>
Texture* AssetManager::loadAsset(asset_id _id, Bundle* _bundle);
}
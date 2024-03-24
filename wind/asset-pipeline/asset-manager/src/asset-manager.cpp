#include "asset-manager/asset-manager.hpp"

namespace wind {
std::vector<assets::AssetPipe*> assets::PipeRegister::m_pipes;

std::vector<AssetManager::Bundle*> AssetManager::m_bundles;
std::hash<std::string> AssetManager::m_hasher;
std::map<asset_id, std::any> AssetManager::m_preloads;

}
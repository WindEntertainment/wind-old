#include "asset-manager/asset-manager.hpp"

namespace wind {
std::vector<assets::AssetPipe*> assets::PipeRegister::m_pipes;

assets::PipeRegister assets::PipeRegister::m_register = assets::PipeRegister(std::vector<AssetPipe*>{
  new ShaderPipe(),
  new ImagePipe(),
  new DefaultPipe(),
});

std::vector<AssetManager::Bundle*> AssetManager::m_bundles;
std::hash<std::string> AssetManager::m_hasher;
std::map<asset_id, std::any> AssetManager::m_preloads;

} // namespace wind

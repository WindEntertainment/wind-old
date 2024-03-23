#include "asset-manager/asset-manager.hpp"

namespace wind {
std::map<const char*, AssetManager::Bundle*> AssetManager::m_bundles;
}
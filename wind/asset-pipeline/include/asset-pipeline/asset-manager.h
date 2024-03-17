#include "./assets/asset.h"
#include <fstream>
#include <spdlog/spdlog.h>
#include <utils/utils.h>

namespace wind {

class AssetManager {
private:
  static std::map<const char*, std::ifstream> m_bundles;

  static Asset* loadAsset(const char* _key, std::ifstream& file) {
  }

public:
  static void loadBundle(const fs::path& _path) {
    std::ifstream file(_path);
    if (!file.is_open()) {
      spdlog::error("Fail load bundle: fail open file by path: {}", _path.string());
      return;
    }

    m_bundles.insert(std::make_pair(_path.string().c_str(), std::move(file)));
  }

  template <typename T>
    requires std::is_base_of_v<Asset, T>
  static T* getAsset(const char* _key) {
    for (auto& pair : m_bundles) {
      auto asset = loadAsset(pair.first, pair.second);
      if (asset)
        return asset;
    }

    return nullptr;
  }
};

} // namespace wind
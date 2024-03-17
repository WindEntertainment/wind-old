#include "asset-pipeline/assets/asset.h"
#include <fstream>
#include <spdlog/spdlog.h>
#include <utils/utils.h>

namespace wind {

class AssetManager {
  struct Bundle {
  private:
    std::ifstream m_file;
    std::map<asset_id, asset_id> m_assets;

  public:
    Bundle(std::ifstream&& _file)
        : m_file(std::move(_file)) {

      m_file.seekg(0, std::ios::beg);

      asset_id header_size;
      header_size = m_file.read(header_size, sizeof(asset_id));
    }

    ~Bundle() {
      m_file.close();
    }
  };

private:
  static std::map<const char*, Bundle*> m_bundles;

  static Asset* loadAsset(const char* _name, Bundle* _bundle) {
  }

public:
  static void loadBundle(const fs::path& _path) {
    std::ifstream file(_path);
    if (!file.is_open()) {
      spdlog::error("Fail load bundle: fail open file by path: {}", _path.string());
      return;
    }

    m_bundles.insert(std::make_pair(_path.string().c_str(), new Bundle(std::move(file))));
  }

  static void unloadBundles() {
    for (auto& pair : m_bundles)
      delete pair.second;
    m_bundles.clear();
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
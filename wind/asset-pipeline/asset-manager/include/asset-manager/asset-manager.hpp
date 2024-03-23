#include <pipes/pipes-register.hpp>

#include <any>
#include <fstream>
#include <spdlog/spdlog.h>
#include <utils/utils.h>

namespace wind {

class AssetManager {
  struct Bundle {
  private:
    std::ifstream m_file;
    std::map<asset_id, asset_id> m_assets;
    asset_id m_fileSize;

  public:
    Bundle(std::ifstream&& _file)
        : m_file(std::move(_file)) {

      m_file.seekg(0, std::ios::end);
      m_fileSize = m_file.tellg();
      m_file.seekg(0, std::ios::beg);

      asset_id header_size;
      m_file.read(reinterpret_cast<char*>(&header_size), sizeof(asset_id));

      asset_id count = (header_size - sizeof(asset_id)) / (2 * sizeof(asset_id));

      for (asset_id i = 0; i < count; ++i) {
        asset_id id;
        asset_id offset;

        m_file.read(reinterpret_cast<char*>(&id), sizeof(asset_id));
        m_file.read(reinterpret_cast<char*>(&offset), sizeof(asset_id));

        spdlog::debug("Load meta-resource. id: {}, offset: {}", id, offset);
        m_assets.insert(std::make_pair(id, offset));
      }
    }

    ~Bundle() {
      m_file.close();
    }

    bool tryGetOffsetById(asset_id _id, asset_id& _offset, asset_id& _end) {
      if (!m_assets.contains(_id))
        return false;

      _offset = m_assets[_id];

      if (_id + 1 < m_assets.size())
        _end = m_assets[_id + 1];
      else
        _end = m_fileSize;

      return true;
    }

    unsigned char* readBytes(asset_id offset, asset_id size, asset_id& pipe) {
      if (size > m_fileSize)
        return nullptr;

      try {
        unsigned char* bytes = new unsigned char[size];
        asset_id id = 0;

        m_file.seekg(offset);
        m_file.read(reinterpret_cast<char*>(&id), sizeof(asset_id));
        m_file.read(reinterpret_cast<char*>(&bytes), size);

        pipe = id;

        return bytes;
      } catch (std::exception& ex) {
        spdlog::error("Fail readBytes from bundle. Offest: {}, Size: {}", offset, size);
        return nullptr;
      }
    }
  };

private:
  static std::vector<Bundle*> m_bundles;
  static std::hash<std::string> m_hasher;
  static std::map<asset_id, std::any> m_preloads;

  template <typename T>
  static T* loadAsset(asset_id _id, Bundle* _bundle) {
    asset_id begin, end;

    if (!_bundle->tryGetOffsetById(_id, begin, end)) {
      spdlog::debug("Failed get asset by id: {}", _id);
      return nullptr;
    }

    void* asset = nullptr;
    asset_id pipe_id = 0;

    if (auto bytes = _bundle->readBytes(begin, end - begin, pipe_id)) {
      AssetPipe* pipe = asset_pipeline::PipeRegister::getPipe(pipe_id);
      if (!pipe) {
        spdlog::error("[Asset-Manager:loadAsset] Unknow pipe:  {}. AssetId: {}", pipe_id, _id);
        delete[] bytes;
      }

      asset = pipe->load(bytes, end - begin);

      delete[] bytes;
    }

    return static_cast<T*>(asset);
  }

public:
  static void loadBundle(const fs::path& _path) {
    std::ifstream file(_path);
    if (!file.is_open()) {
      spdlog::error("Fail load bundle: fail open file by path: {}", _path.string());
      return;
    }

    m_bundles.push_back(new Bundle(std::move(file)));
  }

  static void unloadBundles() {
    for (auto& bundle : m_bundles)
      delete bundle;
    m_bundles.clear();
  }

  template <typename T>
  static void preload(const char* _key) {
    asset_id id = m_hasher(_key);

    if (m_preloads.contains(id))
      return;

    m_preloads.insert(std::make_pair(
        id,
        std::make_any(std::make_shared(getAsset<T>(_key)))));
  }

  template <typename T>
  static T* getAsset(const char* _key) {
    asset_id id = m_hasher(_key);

    if (m_preloads.contains(id))
      return std::any_cast<std::shared_ptr<T>>(m_preloads[id]).get();

    for (auto& bundle : m_bundles) {
      T* asset = loadAsset<T>(id, bundle);
      if (asset)
        return asset;
    }

    return nullptr;
  }
};

} // namespace wind
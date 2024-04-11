#pragma once
#include <pipes/pipes-register.hpp>

#include <any>
#include <fstream>
#include <spdlog/spdlog.h>
#include <utils/utils.h>

namespace wind {

class AssetManager {
  struct Bundle {
  private:
    std::map<asset_id, asset_id> m_assets;
    asset_id m_fileSize;

  public:
    std::ifstream m_file;

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

    bool determinatePipe(asset_id offset, asset_id size, asset_id& pipe) {
      if (size > m_fileSize)
        return false;

      try {
        asset_id id = 0;

        m_file.seekg(offset);
        m_file.read(reinterpret_cast<char*>(&id), sizeof(asset_id));

        pipe = id;

        return true;
      } catch (std::exception& ex) {
        spdlog::error("Fail readBytes from bundle. Offest: {}, Size: {}", offset, size);
        return false;
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

    if (!_bundle->tryGetOffsetById(_id, begin, end))
      return nullptr;

    asset_id size = end - begin;

    spdlog::debug("Load asset by id {}. begin: {}, end: {}, size: {}", _id, begin, end, size);

    void* asset = nullptr;
    asset_id pipe_id = 0;

    if (_bundle->determinatePipe(begin, size, pipe_id)) {
      assets::AssetPipe* pipe = assets::PipeRegister::getPipe(pipe_id);
      if (!pipe)
        spdlog::error("Failed load asset. unknow pipe:  {}. asset id: {}", pipe_id, _id);

      try {
        asset = pipe->load(_bundle->m_file);
      } catch (std::exception& ex) {
        spdlog::error("Failed load asset by id {} by pipe {}: {}", _id, pipe_id, ex.what());
        return nullptr;
      }
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
      if (asset != nullptr)
        return asset;
    }

    spdlog::debug("Failed get asset. name: '{}', hash: {}", _key, id);
    return nullptr;
  }

  static bool exists(const char* _key) {
    asset_id id = m_hasher(_key);
    asset_id begin, end;

    for (auto& bundle : m_bundles)
      if (bundle->tryGetOffsetById(id, begin, end))
        return true;
    return false;
  }
};
} // namespace wind
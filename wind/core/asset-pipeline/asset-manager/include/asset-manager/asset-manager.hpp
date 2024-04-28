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
    // std::map<asset_id, asset_id> m_assets;
    // std::map<asset_id, asset_id> m_assetsSizes;
    std::vector<asset_id> m_ids;
    std::vector<asset_id> m_offsets;
    std::vector<asset_id> m_ends;
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

      spdlog::debug("Load header. Header size: {}, count: {}", header_size, count);

      for (asset_id i = 0; i < count; ++i) {
        asset_id id;
        asset_id offset;

        m_file.read(reinterpret_cast<char*>(&id), sizeof(id));
        m_file.read(reinterpret_cast<char*>(&offset), sizeof(offset));

        spdlog::debug("Load meta-resource. id: {}, offset: {}", id, offset);
        // m_assets.insert(std::make_pair(id, offset));
        m_ids.push_back(id);
        m_offsets.push_back(offset);
      }

      for (asset_id i = 0; i < count; ++i) {
        asset_id size = 0;
        if (i + 1 < m_offsets.size())
          size = m_offsets[i + 1];
        else
          size = m_fileSize;

        m_ends.push_back(size);
      }
    }

    ~Bundle() {
      m_file.close();
    }

    bool tryGetOffsetById(asset_id _id, asset_id& _offset, asset_id& _end) {
      if (std::find(m_ids.begin(), m_ids.end(), _id) == m_ids.end())
        return false;

      size_t ind = std::distance(m_ids.begin(), std::find(m_ids.begin(), m_ids.end(), _id));
      _offset = m_offsets[ind];
      _end = m_ends[ind] - 12;

      // if (_id + 1 < m_assets.size())
      //   _end = m_assets[_id + 1];
      // else
      //   _end = m_fileSize;

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
    std::ifstream file(_path, std::ios_base::binary);
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

    spdlog::error("Failed get asset. name: '{}', hash: {}", _key, id);
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

#pragma once
#include "asset-pipeline/assets/asset.h"

#include <utils/utils.h>
#include <yaml-cpp/yaml.h>
#include <zlib.h>

namespace wind {

class AssetPipe {
  friend class AssetPipeline;

protected:
  asset_id m_id;

public:
  virtual void config(YAML::Node& config){};

  virtual void compile(const fs::path& _source, const fs::path& _destination) = 0;
  virtual Asset* load(unsigned char* bytes) = 0;

  asset_id id() const {
    return m_id;
  }

  AssetPipe(const char* _id) {
    std::hash<const char*> hasher;
    m_id = hasher(_id);
  }
};

} // namespace wind
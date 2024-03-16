#pragma once
#include "asset-pipeline/assets/asset.h"

#include <utils/utils.h>
#include <yaml-cpp/yaml.h>
#include <zlib.h>

namespace wind {

class AssetPipe {
  friend class AssetPipeline;

protected:
  const char* m_id;

public:
  virtual void config(YAML::Node& config){};

  virtual void compile(const fs::path& _source, const fs::path& _destination) = 0;
  virtual Asset* load(const uint* bytes) = 0;

  const char* id() const {
    return m_id;
  }

  AssetPipe(const char* id)
      : m_id(id){};
};

} // namespace wind
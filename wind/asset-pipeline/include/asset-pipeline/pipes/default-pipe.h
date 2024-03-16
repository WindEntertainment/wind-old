#pragma once
#include "asset-pipeline/assets/asset.h"
#include "pipe.h"

namespace wind {
namespace asset_pipeline {

class DefaultPipe : public AssetPipe {
public:
  virtual void compile(const fs::path& source, const fs::path& destination) override;
  virtual Asset* load(const uint* bytes) override;

  DefaultPipe()
      : AssetPipe("default"){};
};

} // namespace asset_pipeline
} // namespace wind
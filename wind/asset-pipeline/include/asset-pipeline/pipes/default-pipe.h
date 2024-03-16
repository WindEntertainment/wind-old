#pragma once
#include "pipe.h"

namespace wind {
namespace asset_pipeline {

class DefaultPipe : public AssetPipe {
public:
  virtual void compile(const fs::path& source, const fs::path& destination) override;

  DefaultPipe()
      : AssetPipe("default"){};
};

} // namespace asset_pipeline
} // namespace wind
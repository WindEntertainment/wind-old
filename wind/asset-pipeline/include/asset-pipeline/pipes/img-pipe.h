#pragma once
#include "asset-pipeline/pipes/pipe.h"
#include "pipe.h"

namespace wind {
namespace asset_pipeline {

class ImagePipe : public AssetPipe {
public:
  void compile(const fs::path& _source,
               const fs::path& _destination) override;

  ImagePipe()
      : AssetPipe("image"){};
};

} // namespace asset_pipeline
} // namespace wind
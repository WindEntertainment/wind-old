#include "asset-pipeline/assets/asset.h"
#include "pipe.h"

namespace wind {
namespace asset_pipeline {

class ShaderPipe : public AssetPipe {
public:
  void compile(const fs::path& _source, const fs::path& _destination) override;
  Asset* load(const uint* bytes) override;

  ShaderPipe()
      : AssetPipe("shader"){};
};

} // namespace asset_pipeline
} // namespace wind
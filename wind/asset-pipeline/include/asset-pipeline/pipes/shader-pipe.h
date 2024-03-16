#include <asset-pipeline/pipe.h>

namespace wind {
namespace asset_pipeline {

class ShaderPipe : public Pipe {
public:
  void compile(const fs::path& _source, const fs::path& _destination) override;

  ShaderPipe()
      : Pipe("shader"){};
};

} // namespace asset_pipeline
} // namespace wind
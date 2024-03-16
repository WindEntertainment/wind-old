#pragma once
#include <regex>

#include "asset-pipeline.h"
#include "pipes/pipe.h"

namespace wind {
namespace asset_pipeline {

class PipeRegister {
  friend class AssetPipeline;

private:
  static std::vector<std::regex> m_regexs;
  static std::vector<AssetPipe*> m_pipes;

  static AssetPipe* getPipe(fs::path path);
  static AssetPipe* getPipe(const std::string& name);

public:
  static void regPipe(const char* regex, AssetPipe* pipe);
};

} // namespace asset_pipeline
} // namespace wind
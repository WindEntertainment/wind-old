#pragma once
#include <regex>

#include "asset-pipeline.h"
#include "pipe.h"

namespace wind {
namespace asset_pipeline {

class PipeRegister {
  friend class AssetPipeline;

private:
  static std::vector<std::regex> m_regexs;
  static std::vector<Pipe*> m_pipes;

  static Pipe* getPipe(fs::path path);
  static Pipe* getPipe(const std::string& name);

public:
  static void regPipe(const char* regex, Pipe* pipe);
};

} // namespace asset_pipeline
} // namespace wind
#pragma once
#include <regex>

#include "pipes/pipe.h"

namespace wind {
namespace asset_pipeline {

class PipeRegister {
private:
  static std::vector<std::regex> m_regexs;
  static std::vector<AssetPipe*> m_pipes;

public:
  static AssetPipe* getPipe(fs::path path);
  static AssetPipe* getPipe(const std::string& name);

  static void regPipe(const char* regex, AssetPipe* pipe);
};

} // namespace asset_pipeline
} // namespace wind
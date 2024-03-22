#pragma once
#include <regex>

#include "pipes/pipe.h"

namespace wind {
namespace asset_pipeline {

class PipeRegister {
private:
  static std::vector<AssetPipe*> m_pipes;

public:
  static AssetPipe* getPipe(asset_id id);
  static void regPipe(AssetPipe* pipe);
};

} // namespace asset_pipeline
} // namespace wind
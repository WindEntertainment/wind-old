#include <asset-pipeline/pipes-register.h>
#include <spdlog/spdlog.h>

#include <regex>

namespace wind {
namespace asset_pipeline {

std::vector<AssetPipe*> PipeRegister::m_pipes{};

AssetPipe* PipeRegister::getPipe(asset_id _id) {
  for (auto&& pipe : m_pipes)
    if (_id == pipe->id())
      return pipe;

  return nullptr;
}

void PipeRegister::regPipe(AssetPipe* _pipe) {
  m_pipes.push_back(_pipe);
  spdlog::info("PipeRegister: registered new pipe: {}", _pipe->id());
}

} // namespace asset_pipeline
} // namespace wind
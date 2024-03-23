#pragma once
#include "pipe.hpp"

#include "default-pipe.hpp"
#include "img-pipe.hpp"
#include "shader-pipe.hpp"

namespace wind {
namespace asset_pipeline {

class PipeRegister {
private:
  static std::vector<AssetPipe*> m_pipes;

public:
  static AssetPipe* getPipe(asset_id _id) {
    for (auto&& pipe : m_pipes)
      if (_id == pipe->id())
        return pipe;

    return nullptr;
  }

  static void regPipe(AssetPipe* _pipe) {
    m_pipes.push_back(_pipe);
    spdlog::info("PipeRegister: registered new pipe: {}", _pipe->id());
  }
};

} // namespace asset_pipeline
} // namespace wind
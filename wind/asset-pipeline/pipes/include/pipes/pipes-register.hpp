#pragma once
#include "pipe.hpp"

#include "copy-pipe.hpp"
#include "default-pipe.hpp"
#include "img-pipe.hpp"
#include "shader-pipe.hpp"

namespace wind {
namespace assets {

class PipeRegister {
private:
  static std::vector<AssetPipe*> m_pipes;
  static PipeRegister m_register;

public:
  PipeRegister(std::vector<AssetPipe*> pipes) {
    m_pipes = pipes;
  }

  ~PipeRegister() {
    forEach(m_pipes, [](const auto& item) {
      delete item;
    });
  }

  static AssetPipe* getPipe(asset_id _id) {
    for (auto&& pipe : m_pipes)
      if (_id == pipe->id())
        return pipe;

    return nullptr;
  }

  static void regPipe(AssetPipe* _pipe) {
    m_pipes.push_back(_pipe);
    spdlog::debug("PipeRegister: registered new pipe: {}", _pipe->id());
  }
};

} // namespace assets
} // namespace wind

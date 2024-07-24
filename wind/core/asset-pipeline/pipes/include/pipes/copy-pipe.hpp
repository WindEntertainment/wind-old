#pragma once
#include "pipe.hpp"

namespace wind {
namespace assets {

class CopyPipe : public AssetPipe {
public:
#ifdef WIND_PIPE_WRITE
  void compile(const fs::path& _source, const fs::path& _destination) override {
    try {
      fs::copy_file(_source, _destination, fs::copy_options::overwrite_existing);
    } catch (fs::filesystem_error& ex) {
      spdlog::error("Failed copy file from {} to {} because: {}", _source.string(), _destination.string(), ex.what());
      return;
    }
  }
#endif

  void* load(std::ifstream& file) override {
    spdlog::warn("AssetManager can't load raw resource data!");
    return nullptr;
  }

  CopyPipe()
      : AssetPipe("copy"){};
};

} // namespace assets
} // namespace wind
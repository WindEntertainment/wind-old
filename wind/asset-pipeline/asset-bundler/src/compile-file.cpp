#include "asset-bundler/asset-bundler.hpp"
#include "pipes/pipe.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

namespace wind {

namespace assets {

void AssetPipeline::compileFile(const fs::path& _source, const fs::path& _destination, AssetPipe* _pipe) {
  spdlog::info("Compile file: {}", _source.string());

  if (!fs::exists(_source)) {
    spdlog::error("Cannot compile file by specified path {} as it's a non exists location", _source.string());
    return;
  }

  if (fs::is_directory(_source)) {
    spdlog::error("Cannot compile file by specified path {} as it's a directory", _source.string());
    return;
  }

  fs::path destination = _destination;
  destination += c_cacheExtentsion;

  try {
    auto parent_path = destination.parent_path();
    if (!fs::exists(parent_path))
      fs::create_directories(parent_path);

    if (fs::exists(destination) && fs::last_write_time(_source) <= fs::last_write_time(destination))
      return;

    _pipe->compile(_source, destination);
  } catch (std::exception& ex) {
    spdlog::error("Failed compile file by path {}: {}", _source.string(), ex.what());
    return;
  }
}

} // namespace assets
} // namespace wind
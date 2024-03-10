#include "asset-pipeline/asset-pipeline.h"
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <sstream>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

namespace wind {
namespace asset_pipeline {

void AssetPipeline::build(const fs::path& _path) {
  spdlog::info("===========================");
  spdlog::info("Start build directory {}", _path.string());

  fs::recursive_directory_iterator it;
  try {
    it = createRecursiveIterator(_path);
  } catch (std::invalid_argument& ex) {
    spdlog::error(ex.what());
    return;
  }

  for (const auto& entry : it) {
    if (entry.is_directory())
      continue;
    spdlog::info("{}, {}, {}", entry.path().filename().string(), entry.path().filename().extension().string(), entry.path().filename().extension().compare("import-config"));

    if (entry.path().filename().extension().string().compare(".import-config") != 0)
      continue;

    try {
      auto config = YAML::LoadFile(entry.path());
      if (auto options = config["preprocessing"])
        preprocessing(entry.path(), options);
    } catch (std::exception& ex) {
      spdlog::error("Failed preprocessing with import-config: {}. Why: {}", entry.path().string(), ex.what());
      return;
    }
  }
}

void AssetPipeline::preprocessing(const fs::path& _path, YAML::Node& _options) {
  for (auto option : _options)
    if (option.first.as<std::string>().compare("execute")) {
      std::stringstream ss;
      ss << _path << "/" << option.second.as<std::string>();
      try {
        system(ss.str().c_str());
      } catch (std::exception& ex) {
        spdlog::error("Failed execute shell command '{}' for preprocessing: {}", ss.str().c_str(), ex.what());
        return;
      }
    }
}

} // namespace asset_pipeline
} // namespace wind
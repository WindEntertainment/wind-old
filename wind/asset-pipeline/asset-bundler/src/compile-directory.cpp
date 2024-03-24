#include "asset-bundler/asset-bundler.hpp"
#include "pipes/pipe.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

namespace wind {

namespace assets {

void AssetPipeline::compileDirectory(const fs::path& _source, const fs::path& _destination, const YAML::Node& config) {
  Stopwatch sw("Compiled");

  const fs::path sourceParentPath = _source.parent_path();

  fs::recursive_directory_iterator it;
  try {
    it = createRecursiveIterator(_source);
  } catch (AssetBundlerError& ex) {
    spdlog::error("Cannot create directory iterator: {}", ex.what());
    return;
  }

  try {
    spdlog::info("Run compiling process...");
    if (auto options = config["exports"])
      for (const auto& entry : it) {
        if (entry.is_directory() || entry.path().filename() == ".export-config" || entry.path().filename().extension() == ".export-config")
          continue;

        YAML::Node exportNode;
        for (auto option : config["exports"]) {
          auto exportPath = option["path"];
          if (!exportPath) {
            spdlog::error("Export elements must have path option: {}", _source.string());
            continue;
          }

          if (!exportPath.IsScalar()) {
            spdlog::error("Export path must be string type: {}", _source.string());
            continue;
          }

          std::regex regex;
          try {
            regex = std::regex(exportPath.as<std::string>());
          } catch (std::regex_error& ex) {
            spdlog::error("Invalid regex expression in path option {}:\n {}", _source.string(), ex.what());
            continue;
          }

          if (std::regex_match(entry.path().lexically_relative(_source).string(), regex)) {
            exportNode = option.as<YAML::Node>();
            break;
          }
        }

        if (exportNode.IsNull())
          continue;

        AssetPipe* pipe = nullptr;
        if (!exportNode["pipe"]) {
          spdlog::error("Cannot find pipe for compile asset by path '{}'", fs::relative(entry, _source).string());
          continue;
        }

        std::hash<std::string> hasher;
        auto pipeType = exportNode["pipe"].as<std::string>();
        asset_id hashType = hasher(pipeType);

        pipe = PipeRegister::getPipe(hashType);
        if (!pipe) {
          spdlog::warn("Unknown pipe type: '{}'", pipeType);
          continue;
        }

        pipe->config(exportNode);

        compileFile(
          fs::relative(entry, sourceParentPath.parent_path()),
          _destination / fs::relative(entry, sourceParentPath),
          pipe);
      }
  } catch (std::exception& ex) {
    spdlog::error("Failed compiling directory '{}': {}", _source.string(), ex.what());
    return;
  }
}

} // namespace assets
} // namespace wind
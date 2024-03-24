#include "asset-bundler/asset-bundler.hpp"
#include "pipes/pipe.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

namespace wind {

namespace assets {

void AssetPipeline::compileDirectory(const fs::path& _source, const fs::path& _destination) {
  spdlog::info("===========================");
  spdlog::info("Start compiling directory {}", _source.string());

  const fs::path sourceParentPath = _source.parent_path();

  std::function<void(const fs::path&)> processDirectory = [&](const fs::path& _path) {
    auto configPath = _path / ".export-config";
    if (!fs::exists(configPath))
      return;

    YAML::Node config;
    try {
      config = YAML::LoadFile(configPath);
      spdlog::info("Start processing directory: '{}'", _path.string());
    } catch (std::exception& ex) {
      spdlog::error("Failed open export config: {}", _path.string());
      return;
    }

    try {
      spdlog::info("Run preprocessing commands...");
      if (auto options = config["preprocessing"])
        preprocessing(configPath, options);
    } catch (std::exception& ex) {
      spdlog::error("Failed preprocessing with export-config: {}: {}", configPath.string(), ex.what());
      return;
    }

    fs::recursive_directory_iterator it;
    try {
      it = fs::recursive_directory_iterator(_path);
    } catch (std::exception& ex) {
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
              spdlog::error("Export elements must have path option: {}", _path.string());
              continue;
            }

            if (!exportPath.IsScalar()) {
              spdlog::error("Export path must be string type: {}", _path.string());
              continue;
            }

            std::regex regex;
            try {
              regex = std::regex(exportPath.as<std::string>());
            } catch (std::regex_error& ex) {
              spdlog::error("Invalid regex expression in path option {}:\n {}", _path.string(), ex.what());
              continue;
            }

            if (std::regex_match(entry.path().lexically_relative(_path).string(), regex)) {
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

          compileFile(fs::relative(entry, _source),
            _destination / fs::relative(entry, sourceParentPath),
            pipe);
        }
    } catch (std::exception& ex) {
      spdlog::error("Failed compiling directory '{}': {}", _path.string(), ex.what());
      return;
    }

    try {
      it = fs::recursive_directory_iterator(_path);
    } catch (std::exception& ex) {
      spdlog::error("Cannot create directory iterator: {}", ex.what());
      return;
    }

    try {
      spdlog::info("Run compiling child directories...");
      if (auto options = config["exports"]) {
        for (const auto& entry : it) {
          if (!entry.is_directory())
            continue;

          bool isMatch = false;
          for (auto option : config["exports"]) {
            auto exportPath = option["path"];
            if (!exportPath) {
              spdlog::error("Export elements must have path option: {}", _path.string());
              continue;
            }

            if (!exportPath.IsScalar()) {
              spdlog::error("Export path must be string type: {}", _path.string());
              continue;
            }

            std::regex regex;
            try {
              regex = std::regex(exportPath.as<std::string>());
            } catch (std::regex_error& ex) {
              spdlog::error("Invalid regex expression in path option {}:\n {}", _path.string(), ex.what());
              continue;
            }

            if (std::regex_match(entry.path().lexically_relative(_path).string(), regex)) {
              isMatch = true;
              break;
            }
          }

          if (isMatch)
            processDirectory(entry.path());
        }
      }
    } catch (std::exception& ex) {
      spdlog::error("Failed compiling child directories: {}", ex.what());
      return;
    }
  };

  Stopwatch sw("Compiled");
  processDirectory(_source);
}

} // namespace assets
} // namespace wind
#include <fmt/core.h>
#include <functional>
#include <regex>
#include <spdlog/spdlog.h>
#include <string>
#include <yaml-cpp/mark.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>

#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <stdexcept>

#include "asset-pipeline/pipe.h"
#include "asset-pipeline/pipes-register.h"

namespace wind {
namespace asset_pipeline {

void AssetPipeline::compileFile(const fs::path& _source,
                                const fs::path& _destination,
                                Pipe* _pipe) {
  spdlog::info("Compile file: {}", _source.string());

  if (!fs::exists(_source)) {
    spdlog::error(
        "Cannot compile file by specified path {} as it's a non exists location",
        _source.string());
    return;
  }

  if (fs::is_directory(_source)) {
    spdlog::error(
        "Cannot compile file by specified path {} as it's a directory. Use --folder flag to compile all files in the directory.",
        _source.string());
    return;
  }

  if (!_pipe) {
    _pipe = PipeRegister::getPipe(_source);
    //_pipe->config(std::move(findConfigForPath(_source.relative_path())));
  }
  if (!_pipe) {
    spdlog::error("Cannot find pipe for compile asset by path {}",
                  _source.string());
    return;
  }

  fs::path destination = _destination;
  destination += ".obj";

  try {
    auto parent_path = destination.parent_path();
    if (!fs::exists(parent_path))
      fs::create_directories(parent_path);

    if (fs::exists(destination) &&
        fs::last_write_time(_source) <= fs::last_write_time(destination))
      return;

    _pipe->compile(_source, destination);
  } catch (std::exception& ex) {
    spdlog::error("Failed compile file by path {}: {}", _source.string(), ex.what());
    return;
  }
}

void AssetPipeline::compileDirectory(const fs::path& _source,
                                     const fs::path& _destination) {
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

          Pipe* pipe = nullptr;
          if (exportNode["pipe"]) {
            pipe = PipeRegister::getPipe(exportNode["pipe"].as<std::string>());
            pipe->config(exportNode);
          }

          compileFile(fs::relative(entry, _source),
                      _destination / fs::relative(entry, sourceParentPath),
                      pipe);
        }
    } catch (std::exception& ex) {
      spdlog::error("Failed compiling directory {}: {}", _path.string(), ex.what());
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

void AssetPipeline::clearUnusedCache(const fs::path& _source, const fs::path& _cache) {
  fs::recursive_directory_iterator cache_it;
  try {
    cache_it = createRecursiveIterator(_cache);
  } catch (std::invalid_argument& ex) {
    spdlog::error(ex.what());
    return;
  }

  const fs::path cacheParentPath = _source.parent_path();

  Stopwatch sw("Clear unused cache");
  for (const auto& entry : cache_it) {
    if (entry.is_directory())
      continue;

    fs::path sourceFile = "./" / fs::relative(entry, _cache);
    sourceFile.replace_extension();

    if (fs::exists(sourceFile))
      continue;

    fs::remove(entry);
  }
}

void AssetPipeline::linkDirectory(const fs::path& _source,
                                  const fs::path& _destination) {
  spdlog::info("===========================");
  spdlog::info("Start linking files in directory {}", _source.string());

  fs::recursive_directory_iterator it;
  try {
    it = createRecursiveIterator(_source);
  } catch (std::invalid_argument& ex) {
    spdlog::error(ex.what());
    return;
  }

  std::ofstream bundle(_destination, std::ios_base::binary);
  if (!bundle.is_open()) {
    spdlog::error("Cannot create file for create bundle by path {}",
                  _destination.string());
    return;
  }

  Stopwatch sw("Linked");
  for (const auto& entry : it) {
    if (entry.is_directory())
      continue;

    std::ifstream file(entry.path(), std::ios_base::binary);
    if (!file.is_open()) {
      spdlog::warn("Cannot read entry in directory {}",
                   entry.path().string());
      continue;
    }

    bundle << file.rdbuf();
  }
}

void AssetPipeline::setConfig(const fs::path& _importConfigPath) {
  spdlog::info("Load config: {}", _importConfigPath.string());

  YAML::Node importConfigRoot;

  try {
    importConfigRoot = YAML::LoadFile(_importConfigPath);
  } catch (YAML::ParserException& ex) {
    spdlog::error("{}, {}", _importConfigPath.string(), ex.what());
    return;
  } catch (std::exception& ex) {
    spdlog::error("{}", ex.what());
    return;
  }

  auto config = importConfigRoot["import-config"];
  if (!config || !config.IsSequence()) {
    spdlog::error("{} should have 'import-config' sequence",
                  _importConfigPath.string());
    return;
  }

  m_importConfig = config;
}

fs::recursive_directory_iterator AssetPipeline::createRecursiveIterator(const fs::path& _path) {
  if (!fs::exists(_path))
    throw std::invalid_argument(fmt::format(
        "Cannot create recursive directory iterator by specified path {} as it's a non exists location",
        _path.string()));

  if (!fs::is_directory(_path))
    throw std::invalid_argument(fmt::format(
        "Cannot create recursive directory iterator by specified path {} as it's a file. Don't use --folder flag to compile separate file.",
        _path.string()));

  fs::recursive_directory_iterator it;
  try {
    it = fs::recursive_directory_iterator(_path);
  } catch (fs::filesystem_error& ex) {
    throw std::invalid_argument(
        fmt::format("Cannot create recursive directory iterator for {}",
                    _path.string()));
  }

  return it;
}

YAML::Node AssetPipeline::findConfigForPath(const fs::path& path) {
  if (!m_importConfig.IsSequence())
    return YAML::Node();

  for (auto map : m_importConfig)
    if (fs::path(map["file"].as<std::string>()).compare(path))
      return map;

  return YAML::Node();
}

} // namespace asset_pipeline
} // namespace wind

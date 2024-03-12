#include "asset-pipeline/asset-pipeline.h"

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

    if (entry.path().filename().string().compare(".import-config") != 0 &&
        entry.path().filename().extension().string().compare(".import-config") != 0)
      continue;

    try {
      auto config = YAML::LoadFile(entry.path());
      if (auto options = config["preprocessing"])
        preprocessing(entry.path(), options);
    } catch (std::exception& ex) {
      spdlog::error("Failed preprocessing with import-config: {}: {}", entry.path().string(), ex.what());
      return;
    }
  }
}

void AssetPipeline::preprocessing(const fs::path& _path, YAML::Node& _options) {
  if (!_options.IsMap()) {
    yamlError("Failed parsing '{}': preprocessing options must be map.", _options, _path.string());
    return;
  }

  for (auto option : _options) {
    if (!option.first.IsScalar() || !option.second.IsScalar()) {
      yamlError("Failed parsing '{}': preprocessing option must be scalar type.", _options, _path.string());
      continue;
    }

    auto preprocessing_step = option.first.as<std::string>();
    if (preprocessing_step.compare("execute")) {
      std::stringstream ss;
      ss << _path << "/" << option.second.as<std::string>();

      auto command = ss.str();
      spdlog::info("Execute: {}", command);

      try {
        system(command.c_str());
      } catch (std::exception& ex) {
        yamlError("Failed execute shell command '{}' for preprocessing: {}", _options, command.c_str(), ex.what());
        return;
      }
    } else {
      yamlWarn("When parsing '{}' ignoring unknown option: '{}'", option, _path.string(), preprocessing_step);
    }
  }
}

} // namespace asset_pipeline
} // namespace wind
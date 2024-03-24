#include "asset-bundler/asset-bundler.hpp"
#include <filesystem>

namespace wind {
namespace assets {

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
    if (preprocessing_step.compare("execute") == 0) {
      std::stringstream ss;
      ss << "cd " << _path.parent_path() << " && " << option.second.as<std::string>();

      auto command = ss.str();
      spdlog::info("Execute: {}", command);

      try {
        system(command.c_str());
      } catch (std::exception& ex) {
        yamlError("Failed execute shell command '{}' for preprocessing: {}", option.second, command.c_str(), ex.what());
        return;
      }
    } else {
      yamlWarn("When parsing '{}' ignoring unknown option: '{}'", option.first, _path.string(), preprocessing_step);
    }
  }
}

} // namespace assets
} // namespace wind
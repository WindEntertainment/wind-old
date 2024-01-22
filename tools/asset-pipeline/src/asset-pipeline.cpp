#include "asset-pipeline/asset-pipeline.h"

#include <spdlog/spdlog.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <cstddef>
#include <exception>
#include <filesystem>
#include <stdexcept>

namespace wind {
namespace asset_pipeline {

void AssetPipeline::load(fs::path _importConfigPath) {
    if (fs::is_directory((_importConfigPath)))
        _importConfigPath /= ".import-config";

    YAML::Node importConfig;

    try {
        importConfig = YAML::LoadFile(_importConfigPath.string().c_str());
    } catch (YAML::ParserException& ex) {
        spdlog::error("{} {}", _importConfigPath.string(), ex.what());
        return;
    } catch (std::exception& ex) {
        spdlog::error("{}", ex.what());
        return;
    }

    auto loaders = importConfig["loaders"];
    if (!loaders || !loaders.IsSequence()) {
        spdlog::error("{} should have 'loaders' sequence", _importConfigPath.string());
        return;
    }

    try {
        for (size_t i = 0; i < loaders.size(); ++i) {
            auto line = loaders[i];
            if (!line.IsMap())
                throw std::invalid_argument("field of loaders should be map");

            for (YAML::const_iterator it = line.begin(); it != line.end(); ++it) {
                spdlog::info("{}", it->second.as<string>());
            }
        }
    } catch (std::exception& ex) {
        spdlog::error("({}) incorrect data format: {}", _importConfigPath.string(), ex.what());
        return;
    }
}

}  // namespace asset_pipeline
}  // namespace wind

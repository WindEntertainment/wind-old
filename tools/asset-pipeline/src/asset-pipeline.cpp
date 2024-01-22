#include <spdlog/spdlog.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <filesystem>

#include "asset-pipeline/pipes-register.h"

namespace wind {
namespace asset_pipeline {

void AssetPipeline::compileFile(const fs::path& _path, const fs::path& _destination) {
    if (fs::is_directory(_path)) {
        spdlog::error(
            "Can't load file by path {} because it's directory. Use AssetPipeline::loadDirectory "
            "for load all file in directory",
            _path.string());
        return;
    }

    Pipe pipe;

    if (!PipeRegister::tryGetPipe(_path, pipe)) {
        spdlog::error("Can't find pipe for compile asset by path {}", _path.string());
        return;
    }

    pipe.compile(_path, _destination);
}

}  // namespace asset_pipeline
}  // namespace wind

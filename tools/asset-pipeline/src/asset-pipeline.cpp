#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <filesystem>

#include "asset-pipeline/pipes-register.h"

namespace wind {
namespace asset_pipeline {

void AssetPipeline::compileFile(const fs::path& _source, const fs::path& _destination) {
    if (fs::is_directory(_source)) {
        spdlog::error(
            "Can't compile file by path {} because it's directory. Use "
            "AssetPipeline::loadDirectory for compile all file in directory",
            _source.string());
        return;
    }

    Pipe* pipe;

    if (!PipeRegister::tryGetPipe(_source, pipe)) {
        spdlog::error("Can't find pipe for compile asset by path {}", _source.string());
        return;
    }

    pipe->compile(_source, _destination);
}

void AssetPipeline::compileDirectory(const fs::path& _source, const fs::path& _destination,
                                     const fs::path& _cache) {
    if (!fs::is_directory(_source)) {
        spdlog::error(
            "Can't compile directory by path {} because it's file. Use "
            "AssetPipeline::compileDirectory to compile separate file",
            _source.string());
        return;
    }

    fs::recursive_directory_iterator it;
    try {
        it = fs::recursive_directory_iterator(_source);
    } catch (fs::filesystem_error& ex) {
        spdlog::error("Can't create recursive directory iterator for {}", _source.string());
        return;
    }

    Stopwatch sw(fmt::format("Compile directory {}", _source.string()));
    for (const auto& entry : it) {
        if (entry.is_directory())
            continue;

        spdlog::info("compile {}", entry.path().string());
        compileFile(entry, _cache / entry.path().filename());
    }
}

}  // namespace asset_pipeline
}  // namespace wind

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
    spdlog::info("Compile file: {}", _source.string());

    if (!fs::exists(_source)) {
        spdlog::error("Cannot compile file by specified path {} as it's a non exists location",
                      _source.string());
        return;
    }

    if (fs::is_directory(_source)) {
        spdlog::error(
            "Cannot compile file by specified path {} as it's a directory. Use "
            "AssetPipeline::compileDirectory to compile all files in the directory.",
            _source.string());
        return;
    }

    Pipe* pipe = PipeRegister::getPipe(_source);
    if (!pipe) {
        spdlog::error("Can't find pipe for compile asset by path {}", _source.string());
        return;
    }

    pipe->compile(_source, _destination);
}

void AssetPipeline::compileDirectory(const fs::path& _source, const fs::path& _destination,
                                     const fs::path& _cache) {
    if (!fs::is_directory(_source)) {
        spdlog::error(
            "Cannot compile file by specified path {} as it's a file. Use "
            "AssetPipeline::compileFile to compile separate file.",
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

    spdlog::info("===========================");
    spdlog::info("Start compiling directory {}", _source.string());

    Stopwatch sw("Compiled");
    for (const auto& entry : it) {
        if (entry.is_directory())
            continue;

        compileFile(entry, _cache / entry.path().filename());
    }
}

}  // namespace asset_pipeline
}  // namespace wind

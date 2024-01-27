#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <stdexcept>

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
        spdlog::error("Cannot find pipe for compile asset by path {}", _source.string());
        return;
    }

    fs::path destination = _destination;
    destination += ".obj";

    try {
        auto parent_path = destination.parent_path();
        if (!fs::exists(parent_path))
            fs::create_directory(parent_path);

        if (fs::exists(destination) &&
            fs::last_write_time(_source) <= fs::last_write_time(destination))
            return;

        pipe->compile(_source, destination);
    } catch (std::exception& ex) {
        spdlog::error("Failed compile file by path {}: {}", _source.string(), ex.what());
        return;
    }
}

void AssetPipeline::compileDirectory(const fs::path& _source, const fs::path& _destination) {
    spdlog::info("===========================");
    spdlog::info("Start compiling directory {}", _source.string());

    fs::recursive_directory_iterator it;
    try {
        it = createRecursiveIterator(_source);
    } catch (std::invalid_argument& ex) {
        spdlog::error(ex.what());
        return;
    }

    Stopwatch sw("Compiled");
    for (const auto& entry : it) {
        if (entry.is_directory())
            continue;

        compileFile(entry, _destination / entry.path().filename());
    }
}

void AssetPipeline::clearUnusedCache(const fs::path& _source, const fs::path& _cache) {
    fs::recursive_directory_iterator cache_it;
    try {
        cache_it = createRecursiveIterator(_cache);
    } catch (std::invalid_argument& ex) {
        spdlog::error(ex.what());
        return;
    }

    Stopwatch sw("Clear unused cache");
    for (const auto& entry : cache_it) {
        if (entry.is_directory())
            continue;

        fs::path sourceFile = _source / entry.path().filename();
        sourceFile.replace_extension();

        if (fs::exists(sourceFile))
            continue;

        fs::remove(entry);
    }
}

void AssetPipeline::linkDirectory(const fs::path& _source, const fs::path& _destination) {
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
        spdlog::error("Cannot create file for create bundle by path {}", _destination.string());
        return;
    }

    Stopwatch sw("Linked");
    for (const auto& entry : it) {
        if (entry.is_directory())
            continue;

        std::ifstream file(entry.path(), std::ios_base::binary);
        if (!file.is_open()) {
            spdlog::warn("Cannot read entry in directory {}", entry.path().string());
            continue;
        }

        bundle << file.rdbuf();
    }
}

void AssetPipeline::setConfig(const fs::path& _importConfigPath) {
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
        spdlog::error("{} should have 'import-config' sequence", _importConfigPath.string());
        return;
    }

    m_importConfig = config;
}

fs::recursive_directory_iterator AssetPipeline::createRecursiveIterator(const fs::path& _path) {
    if (!fs::exists(_path))
        throw std::invalid_argument(
            fmt::format("Cannot create recursive directory iterator by specified path {} as "
                        "it's a non exists "
                        "location",
                        _path.string()));

    if (!fs::is_directory(_path))
        throw std::invalid_argument(
            fmt::format("Cannot create recursive directory iterator by specified path {} as "
                        "it's a file. Use "
                        "AssetPipeline::compileFile to compile separate file.",
                        _path.string()));

    fs::recursive_directory_iterator it;
    try {
        it = fs::recursive_directory_iterator(_path);
    } catch (fs::filesystem_error& ex) {
        throw std::invalid_argument(
            fmt::format("Cannot create recursive directory iterator for {}", _path.string()));
    }

    return it;
}

}  // namespace asset_pipeline
}  // namespace wind

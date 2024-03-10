#include <asset-pipeline/pipes-register.h>
#include <asset-pipeline/pipes/content-3d-pipe.h>
#include <asset-pipeline/pipes/default-pipe.h>
#include <asset-pipeline/pipes/img-pipe.h>
#include <asset-pipeline/pipes/shader-pipe.h>
#include <spdlog/spdlog.h>

#include <cxxopts.hpp>

#include "asset-pipeline/asset-pipeline.h"

void setting() {
  using namespace wind;

  asset_pipeline::PipeRegister::regPipe(".*\\.jpg", new asset_pipeline::ImgPipe());
  asset_pipeline::PipeRegister::regPipe(".*\\.obj", new asset_pipeline::Content3DPipe());
  asset_pipeline::PipeRegister::regPipe(".*\\.glsl", new asset_pipeline::ShaderPipe());
  asset_pipeline::PipeRegister::regPipe(".*\\.*", new asset_pipeline::DefaultPipe());
}

int main(int argc, char** argv) {
  // clang-format off
    cxxopts::Options conf_options(
        "wind-asset",
        "Asset-Pipeline Tool. Version: 0.1a.\n"
                    "Is part of the Wind project.\n"
                    "Distributed under the terms of the MIT License.\n");
  // clang-format on

  // clang-format off
    conf_options.add_options()
        ("h, help", "Print usage")
        ("s, source", "Source file/folder", cxxopts::value<std::string>())
        ("o, output", "Output file", cxxopts::value<std::string>())
        ("f, folder", "Set compile target as folder")
        ("l, link", "Linking all files in cache folder to bundle")
        ("c, cache", "Cache folder (only if you use linking)", cxxopts::value<std::string>())
        ("i, config", "Use {source folder}/.import-config file for compile directory");
  // clang-format on

  auto options = conf_options.parse(argc, argv);

  bool printHelp = options.count("help") || !options.count("source") || !options.count("output");
  if (printHelp) {
    std::cout << conf_options.help() << std::endl;
    return EXIT_SUCCESS;
  }

  using namespace wind;
  using namespace wind::asset_pipeline;

  AssetPipeline pipeline;
  setting();

  fs::path source = options["source"].as<std::string>();
  fs::path output = options["output"].as<std::string>();

  bool useFolder = options.count("folder");
  bool useConfig = options.count("config");
  bool useCache = options.count("cache");
  bool useLink = options.count("link");

  if (useFolder) {
    if (useConfig)
      pipeline.setConfig(source / ".import-config");

    fs::path destination =
        useCache ? fs::path(options["cache"].as<std::string>()) : output;

    if (useCache)
      pipeline.clearUnusedCache(source, destination);

    pipeline.compileDirectory(source, destination);

    if (useLink)
      pipeline.linkDirectory(destination, output);
  } else {
    pipeline.compileFile(source, output);
  }

  return EXIT_SUCCESS;
}
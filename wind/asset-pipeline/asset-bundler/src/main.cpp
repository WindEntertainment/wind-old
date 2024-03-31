#define WIND_PIPE_WRITE

#define STB_IMAGE_IMPLEMENTATION

#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

#include "asset-bundler/asset-bundler.hpp"

int main(int argc, char** argv) {
  // clang-format off
  cxxopts::Options conf_options(
      "wind-asset-bundler",
      "Asset-Bundler Tool. Version: 0.3a.\n"
      "Is part of the Wind project.\n"
      "Distributed under the terms of the MIT License.\n"
  );
  // clang-format on

  // clang-format off
  conf_options.add_options()
      ("h, help", "Print usage")
      ("b, build", "Build directory", cxxopts::value<std::string>());
  // clang-format on

  auto options = conf_options.parse(argc, argv);

  bool printHelp = options.count("help") || !options.count("build");
  if (printHelp) {
    std::cout << conf_options.help() << std::endl;
    return EXIT_SUCCESS;
  }

  using namespace wind;
  using namespace wind::asset_pipeline;

  AssetPipeline pipeline;
  setting();

  bool useBuild = options.count("build");
  if (useBuild) {
    fs::path source = options["build"].as<std::string>();
    pipeline.build(source);
  } else {
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
      pipeline.compileFile(source, output, nullptr);
    }
  }

  return EXIT_SUCCESS;
}

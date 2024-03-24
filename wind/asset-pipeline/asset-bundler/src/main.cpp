#define WIND_PIPE_WRITE

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
  using namespace wind::assets;

  AssetPipeline pipeline;
  PipeRegister::regPipe(new ShaderPipe());
  PipeRegister::regPipe(new ImagePipe());
  PipeRegister::regPipe(new DefaultPipe());

  fs::path source = options["build"].as<std::string>();
  pipeline.build(source);

  return EXIT_SUCCESS;
}
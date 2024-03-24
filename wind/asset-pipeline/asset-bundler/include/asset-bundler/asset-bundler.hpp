#pragma once
#define WIND_PIPE_WRITE

#include <utils/utils.h>
#include <utils/yaml-utils.h>

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>

#include "pipes/pipe.hpp"
#include "pipes/pipes-register.hpp"

#include "asset-bundler/asset-bundler-error.hpp"

namespace wind {
namespace assets {

class AssetPipeline {
public:
  void build(const fs::path& source);

private:
  void clearUnusedCache(const fs::path& source, const fs::path& cache);
  void compileDirectory(const fs::path& source, const fs::path& destination);
  void preprocessing(const fs::path& path, YAML::Node& options);
  void compileFile(const fs::path& source, const fs::path& destination, AssetPipe* pipe);
  void linkDirectory(const fs::path& source, const fs::path& destination);

  fs::recursive_directory_iterator createRecursiveIterator(const fs::path& path);
};

} // namespace assets
} // namespace wind
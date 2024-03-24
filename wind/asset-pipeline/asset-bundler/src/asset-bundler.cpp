#include "asset-bundler/asset-bundler.hpp"

namespace wind {

std::vector<assets::AssetPipe*> assets::PipeRegister::m_pipes;

namespace assets {

void AssetPipeline::build(const fs::path& _path) {
  Stopwatch sw("Builded");

  spdlog::info("===========================");
  spdlog::info("Start build directory {}", _path.string());

  auto cachePath = fs::current_path() / ".cache";
  auto destinationPath = fs::current_path() / "assets.bundle";

  clearUnusedCache(_path, cachePath);
  processDirectory(_path, cachePath);
  linkDirectory(cachePath, destinationPath);
}

fs::recursive_directory_iterator AssetPipeline::createRecursiveIterator(const fs::path& _path) {
  if (!fs::exists(_path))
    throw AssetBundlerError(
      "Cannot create recursive directory iterator by specified path {} as it's a non exists location",
      _path.string());

  if (!fs::is_directory(_path))
    throw AssetBundlerError(
      "Cannot create recursive directory iterator by specified path {} as it's a file. ",
      _path.string());

  fs::recursive_directory_iterator it;
  try {
    it = fs::recursive_directory_iterator(_path);
  } catch (fs::filesystem_error& ex) {
    throw AssetBundlerError(
      "Cannot create recursive directory iterator for {}. what: ",
      _path.string(),
      ex.what());
  }

  return it;
}

} // namespace assets
} // namespace wind

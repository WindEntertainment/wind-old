#include "asset-bundler/asset-bundler.hpp"

namespace wind {

std::vector<assets::AssetPipe*> assets::PipeRegister::m_pipes;

// clang-format off
assets::PipeRegister assets::PipeRegister::m_register =  assets::PipeRegister(std::vector<AssetPipe*>{
  new ShaderPipe(),
  new ImagePipe(),
  new DefaultPipe(),
  new CopyPipe()
});
// clang-format on

namespace assets {

void AssetBundler::build(const fs::path& _path) {
  Stopwatch sw("Builded");

  spdlog::info("===========================");
  spdlog::info("Start build directory {}", _path.string());

  auto cachePath = fs::current_path() / ".cache";
  auto outputPath = fs::current_path().parent_path() / "res";

  if (!fs::exists(outputPath))
    fs::create_directory(outputPath);

  // clearUnusedCache(_path, cachePath);
  processDirectory(_path, cachePath);

  fs::directory_iterator it;
  try {
    it = fs::directory_iterator(cachePath);
  } catch (fs::filesystem_error ex) {
    spdlog::error("Failed create directory iterator for {} directory: {}", cachePath.string(), ex.what());
    return;
  }

  for (const auto& entry : it) {
    auto ext = entry.path().extension().string();
    if (ext == ".bundle")
      linkDirectory(entry.path(), outputPath / entry.path().filename());
    else if (ext == ".directory") {
      auto destination = outputPath / entry.path().filename();
      destination.replace_extension();

      exportDirectory(entry.path(), destination);
    }
  }
}

fs::recursive_directory_iterator AssetBundler::createRecursiveIterator(const fs::path& _path) {
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

#include "asset-bundler/asset-bundler.hpp"

namespace wind {

std::vector<assets::AssetPipe*> assets::PipeRegister::m_pipes;

namespace assets {

fs::recursive_directory_iterator AssetPipeline::createRecursiveIterator(const fs::path& _path) {
  if (!fs::exists(_path))
    throw new AssetBundlerError(
      "Cannot create recursive directory iterator by specified path {} as it's a non exists location",
      _path.string());

  if (!fs::is_directory(_path))
    throw new AssetBundlerError(
      "Cannot create recursive directory iterator by specified path {} as it's a file. Don't use --folder flag to compile separate file.",
      _path.string());

  fs::recursive_directory_iterator it;
  try {
    it = fs::recursive_directory_iterator(_path);
  } catch (fs::filesystem_error& ex) {
    throw new AssetBundlerError(
      "Cannot create recursive directory iterator for {}",
      _path.string());
  }

  return it;
}

} // namespace assets
} // namespace wind

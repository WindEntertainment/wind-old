#include "asset-bundler/asset-bundler.hpp"

namespace wind {
namespace assets {

void AssetBundler::exportDirectory(const fs::path& _source, const fs::path& _destination) {
  Stopwatch sw("Exportred");

  spdlog::info("Export directory {} to {}", _source.string(), _destination.string());

  fs::recursive_directory_iterator it;
  try {
    it = createRecursiveIterator(_source);
  } catch (AssetBundlerError& ex) {
    spdlog::error("Cannot create directory iterator: {}", ex.what());
    return;
  }

  for (const auto& entry : it) {
    if (entry.is_directory())
      continue;

    auto ext = entry.path().extension().string();
    if (ext != c_cacheExtentsion)
      continue;

    auto name = entry.path().filename().replace_extension();
    auto destination = _destination / name;

    if (!fs::exists(destination.parent_path()))
      fs::create_directories(destination.parent_path());

    try {
      spdlog::info("Export file: {} to {}", name.string(), destination.string());
      fs::copy_file(entry.path(), destination, fs::copy_options::overwrite_existing);
    } catch (fs::filesystem_error& ex) {
      spdlog::error("Failed to export file from {}: {}", entry.path().string(), ex.what());
    }
  }
}

} // namespace assets
} // namespace wind
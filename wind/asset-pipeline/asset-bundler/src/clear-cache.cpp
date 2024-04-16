#include "asset-bundler/asset-bundler.hpp"
#include "pipes/pipe.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

namespace wind {

namespace assets {

void AssetBundler::clearUnusedCache(const fs::path& _source, const fs::path& _cache) {
  if (!fs::exists(_cache))
    return;

  Stopwatch sw("Clear unused cache");

  fs::recursive_directory_iterator cache_it;
  try {
    cache_it = createRecursiveIterator(_cache);
  } catch (AssetBundlerError& ex) {
    spdlog::error(ex.what());
    return;
  }

  const fs::path cacheParentPath = _source.parent_path();
  for (const auto& entry : cache_it) {
    if (entry.is_directory())
      continue;

    fs::path sourceFile = "./" / fs::relative(entry, _cache);
    if (sourceFile.extension().string() != c_cacheExtension)
      return;

    sourceFile.replace_extension();

    if (fs::exists(sourceFile))
      continue;

    fs::remove(entry);
  }
}

} // namespace assets
} // namespace wind
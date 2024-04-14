#include "asset-bundler/asset-bundler.hpp"
#include "pipes/pipe.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

namespace wind {

namespace assets {

void AssetBundler::linkDirectory(const fs::path& _source, const fs::path& _destination) {
  Stopwatch sw("Linked");

  spdlog::info("===========================");
  spdlog::info("Start linking files in directory {}", _source.string());

  fs::recursive_directory_iterator it;
  try {
    it = createRecursiveIterator(_source);
  } catch (AssetBundlerError& ex) {
    spdlog::error(ex.what());
    return;
  }

  std::ofstream bundle(_destination, std::ios_base::binary);
  if (!bundle.is_open()) {
    spdlog::error("Cannot create file for create bundle by path {}", _destination.string());
    return;
  }

  std::map<fs::path, std::ifstream> files;
  for (const auto& entry : it) {
    if (entry.is_directory())
      continue;

    std::ifstream file(entry.path(), std::ios_base::binary);
    if (!file.is_open()) {
      spdlog::warn("Cannot read entry in directory {}", entry.path().string());
      continue;
    }

    files.insert(std::make_pair(fs::relative(entry.path(), _source).replace_extension(), std::move(file)));
  }

  asset_id header_size = files.size() * sizeof(asset_id) * 2 + sizeof(asset_id);
  asset_id offset = header_size;

  bundle.write(reinterpret_cast<const char*>(&header_size), sizeof(asset_id));

  spdlog::info("Write bundle header. header size: {}", header_size);

  std::hash<std::string> hasher;
  for (auto& pair : files) {
    asset_id id = hasher(replaceAll(pair.first.string(), "\\", "/"));

    spdlog::info("Write meta-resource. name: '{}', id: {}, offset: {}", pair.first.string(), id, offset);

    bundle.write(reinterpret_cast<const char*>(&id), sizeof(asset_id));
    bundle.write(reinterpret_cast<const char*>(&offset), sizeof(asset_id));

    pair.second.seekg(0, std::ios::end);
    offset += pair.second.tellg();
    pair.second.seekg(0, std::ios::beg);
  }

  for (auto& pair : files)
    bundle << pair.second.rdbuf();
}

} // namespace assets
} // namespace wind

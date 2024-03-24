#include "asset-bundler/asset-bundler.hpp"
#include "pipes/pipe.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

namespace wind {

std::vector<assets::AssetPipe*> assets::PipeRegister::m_pipes;

namespace assets {

void AssetPipeline::setConfig(const fs::path& _importConfigPath) {
  spdlog::info("Load config: {}", _importConfigPath.string());

  YAML::Node importConfigRoot;

  try {
    importConfigRoot = YAML::LoadFile(_importConfigPath);
  } catch (YAML::ParserException& ex) {
    spdlog::error("{}, {}", _importConfigPath.string(), ex.what());
    return;
  } catch (std::exception& ex) {
    spdlog::error("{}", ex.what());
    return;
  }

  auto config = importConfigRoot["import-config"];
  if (!config || !config.IsSequence()) {
    spdlog::error("{} should have 'import-config' sequence", _importConfigPath.string());
    return;
  }

  m_importConfig = config;
}

fs::recursive_directory_iterator AssetPipeline::createRecursiveIterator(const fs::path& _path) {
  if (!fs::exists(_path))
    throw std::invalid_argument(fmt::format(
      "Cannot create recursive directory iterator by specified path {} as it's a non exists location",
      _path.string()));

  if (!fs::is_directory(_path))
    throw std::invalid_argument(fmt::format(
      "Cannot create recursive directory iterator by specified path {} as it's a file. Don't use --folder flag to compile separate file.",
      _path.string()));

  fs::recursive_directory_iterator it;
  try {
    it = fs::recursive_directory_iterator(_path);
  } catch (fs::filesystem_error& ex) {
    throw std::invalid_argument(
      fmt::format("Cannot create recursive directory iterator for {}",
        _path.string()));
  }

  return it;
}

YAML::Node AssetPipeline::findConfigForPath(const fs::path& path) {
  if (!m_importConfig.IsSequence())
    return YAML::Node();

  for (auto map : m_importConfig)
    if (fs::path(map["file"].as<std::string>()).compare(path))
      return map;

  return YAML::Node();
}

} // namespace assets
} // namespace wind

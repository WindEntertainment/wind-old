#include <asset-pipeline/pipes/content-3d-pipe.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/node/node.h>

#include <assimp/Importer.hpp>
#include <exception>
#include <fstream>
#include <ios>
#include <stdexcept>

namespace wind {
namespace asset_pipeline {

void Content3DPipe::compile(const fs::path& _source, const fs::path& _destination) {
  std::ofstream output(_destination, std::ios_base::binary);
  if (!output.is_open()) {
    spdlog::error("Cannot create output file: {}", _destination.string());
    return;
  }

  auto name = _source.c_str();

  output.write(name, strlen(name) + 1);
  output.write(m_id, strlen(m_id) + 1);

  std::stringstream buffer;
  try {
    const struct aiScene* obj = importer.ReadFile(_source.string().c_str(), m_config.flags);

    if (obj == nullptr)
      throw std::invalid_argument(importer.GetErrorString());

    if (obj->mNumMeshes < 1) {
      throw std::invalid_argument(fmt::format("{} must have a mesh!", _source.string()));
    }

    auto mesh = obj->mMeshes[0];
    for (uint i = 0; i < mesh->mNumFaces; ++i)
      if (mesh->mFaces[i].mNumIndices != 3)
        throw std::invalid_argument("Invalid format (face should be only with 3 vertex)");

    buffer << mesh->mNumVertices;
    for (uint i = 0; i < mesh->mNumVertices; ++i)
      buffer << mesh->mVertices[i].x << mesh->mVertices[i].y << mesh->mVertices[i].z;

    buffer << (mesh->mNumFaces * 3);
    for (uint i = 0; i < mesh->mNumFaces; ++i)
      for (uint j = 0; j < 3; ++j) {
        buffer << mesh->mFaces[i].mIndices[j];
      }

    buffer << (bool)mesh->mTextureCoords[0];
    if (mesh->mTextureCoords[0]) {
      for (uint i = 0; i < mesh->mNumVertices; ++i) {
        buffer << mesh->mTextureCoords[0][i].x << mesh->mTextureCoords[0][i].y;
      }
    }
  } catch (std::exception& ex) {
    spdlog::error(ex.what());
    return;
  }

  auto fileContentStr = buffer.str();
  const char* fileContent = fileContentStr.c_str();

  const size_t fileSize = strlen(fileContent) + 1;

  size_t zippedSize = compressBound(fileSize);
  char zipped[zippedSize];

  auto result = compress(reinterpret_cast<Bytef*>(zipped), &zippedSize, reinterpret_cast<const Bytef*>(fileContent), fileSize);
  if (result != Z_OK) {
    spdlog::error("Cannot compress data");
    return;
  }

  output.write(zipped, zippedSize);
}

static std::map<std::string, int> c_aiFlags = {
    {"aiProcess_Triangulate", aiProcess_Triangulate},
    {"aiProcess_FlipUVs", aiProcess_FlipUVs},
    {"aiProcess_CalcTangentSpace", aiProcess_CalcTangentSpace}};

void Content3DPipe::config(YAML::Node& _config) {
  auto flags = _config["flags"];

  if (!flags || !flags.IsSequence())
    return;

  m_config.flags = 0;
  for (auto flag : flags) {
    auto key = flag.as<std::string>();
    if (!c_aiFlags.contains(key)) {
      spdlog::warn("{}: Unknown flag: {}", _config["file"].as<std::string>(), key);
      continue;
    }

    m_config.flags |= c_aiFlags[key];
  }
}

} // namespace asset_pipeline
} // namespace wind
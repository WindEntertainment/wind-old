#pragma once
#include "pipe.hpp"

namespace wind {
namespace asset_pipeline {

class DefaultPipe : public AssetPipe {
public:
#ifdef WIND_PIPE_WRITE
  void compile(const fs::path& _source, const fs::path& _destination) override {
    std::ifstream input(_source, std::ios_base::in);
    std::ofstream output(_destination, std::ios_base::binary);

    if (!input.is_open()) {
      spdlog::error("Cannot open source file: {}", _source.string());
      return;
    }

    if (!output.is_open()) {
      spdlog::error("Cannot open destination file: {}", _destination.string());
      return;
    }

    std::string fileContent;
    {
      std::stringstream buffer;
      buffer << input.rdbuf();
      fileContent = buffer.str();
    }

    size_t zippedSize = compressBound(fileContent.size());
    char* zipped = new char[zippedSize];

    auto result = compress(reinterpret_cast<Bytef*>(zipped), &zippedSize, reinterpret_cast<const Bytef*>(fileContent.c_str()), fileContent.size());
    if (result != Z_OK) {
      spdlog::error("Cannot compress data");
      return;
    }

    auto fileSize = (asset_id)fileContent.size();

    output.write(reinterpret_cast<char*>(&m_id), sizeof(asset_id));
    output.write(reinterpret_cast<char*>(&fileSize), sizeof(asset_id));
    output.write(reinterpret_cast<char*>(&zippedSize), sizeof(asset_id));

    output.write(zipped, zippedSize);

    input.close();
    output.close();

    delete[] zipped;
  }
#endif

  void* load(std::ifstream& file) override {
    asset_id orgSize;
    asset_id zipSize;

    file.read(reinterpret_cast<char*>(&orgSize), sizeof(asset_id));
    file.read(reinterpret_cast<char*>(&zipSize), sizeof(asset_id));

    auto zipData = new unsigned char[zipSize];
    file.read(reinterpret_cast<char*>(zipData), zipSize);

    uLongf orgSizeT = (uLongf)orgSize;
    auto unzipData = new unsigned char[orgSize];

    auto rc = uncompress(unzipData, &orgSizeT, zipData, (uLongf)zipSize);
    if (rc != Z_OK)
      throw std::invalid_argument("Failed uncompress data");

    delete[] zipData;

    return (void*)(unzipData);
  }

  DefaultPipe()
      : AssetPipe("default"){};
};

} // namespace asset_pipeline
} // namespace wind

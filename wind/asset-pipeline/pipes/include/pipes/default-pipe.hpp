#pragma once
#include "pipe.hpp"

namespace wind {
namespace assets {

class DefaultPipe : public AssetPipe {
public:
#ifdef WIND_PIPE_WRITE
  void compile(const fs::path& _source, const fs::path& _destination) override {
    std::ifstream input(_source, std::ios_base::binary);
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

    uLongf zippedSize = compressBound(fileContent.size());
    auto zipped = new Bytef[zippedSize];

    auto result = compress(zipped, &zippedSize, reinterpret_cast<const Bytef*>(fileContent.c_str()), static_cast<uLongf>(fileContent.size()));
    if (result != Z_OK) {
      spdlog::error("Cannot compress data");
      return;
    }

    auto fileSize = (uLongf)fileContent.size();

    output.write(reinterpret_cast<char*>(&m_id), sizeof(m_id));
    output.write(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
    output.write(reinterpret_cast<char*>(&zippedSize), sizeof(zippedSize));
    output.write(reinterpret_cast<const char*>(zipped), zippedSize);

    input.close();
    output.close();

    delete[] zipped;
  }
#endif

  void* load(std::ifstream& file) override {
    uLongf orgSize;
    uLongf zipSize;

    file.read(reinterpret_cast<char*>(&orgSize), sizeof(orgSize));
    file.read(reinterpret_cast<char*>(&zipSize), sizeof(zipSize));

    auto zipData = new Bytef[zipSize];
    file.read(reinterpret_cast<char*>(zipData), zipSize);

    auto unzipData = new Bytef[orgSize];

    auto rc = uncompress(unzipData, &orgSize, zipData, zipSize);
    if (rc != Z_OK)
      throw std::invalid_argument(fmt::format("Failed uncompress data: {}", zError(rc)));

    delete[] zipData;

    return (void*)(unzipData);
  }

  DefaultPipe()
      : AssetPipe("default"){};
};

} // namespace assets
} // namespace wind

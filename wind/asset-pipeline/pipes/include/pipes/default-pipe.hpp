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

    spdlog::info("size: {}, zipped size: {}", static_cast<asset_id>(fileContent.size()), zippedSize);

    auto fileSize32 = (asset_id)fileContent.size();
    auto zippedSize32 = (asset_id)zippedSize;

    output.write(reinterpret_cast<char*>(&m_id), sizeof(m_id));
    output.write(reinterpret_cast<char*>(&fileSize32), sizeof(fileSize32));
    output.write(reinterpret_cast<char*>(&zippedSize32), sizeof(zippedSize32));
    output.write(reinterpret_cast<const char*>(zipped), zippedSize);

    input.close();
    output.close();

    delete[] zipped;
  }
#endif

  void* load(std::ifstream& file) override {
    asset_id orgSize;
    asset_id zipSize;

    file.read(reinterpret_cast<char*>(&orgSize), sizeof(orgSize));
    file.read(reinterpret_cast<char*>(&zipSize), sizeof(zipSize));

    auto zipData = new Bytef[zipSize];
    file.read(reinterpret_cast<char*>(zipData), zipSize);

    uLongf orgSizeT = static_cast<uLongf>(orgSize);
    auto unzipData = new Bytef[orgSize];

    auto rc = uncompress(unzipData, &orgSizeT, zipData, static_cast<uLongf>(zipSize));
    if (rc != Z_OK)
      throw std::invalid_argument(fmt::format("Failed uncompress data: {}", zError(rc)));

    spdlog::info("orgSize: {}, zipSize: {}, orgSizeT: {}", orgSize, zipSize, orgSizeT);

    delete[] zipData;

    return (void*)(unzipData);
  }

  DefaultPipe()
      : AssetPipe("default"){};
};

} // namespace assets
} // namespace wind

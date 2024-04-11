#pragma once
#include "pipe.hpp"

#include <filesystem>
#include <spdlog/spdlog.h>

#ifdef WIND_PIPE_WRITE

#include <stb_image.h>

#endif

namespace wind {
namespace assets {

class ImagePipe : public AssetPipe {
public:
#ifdef WIND_PIPE_WRITE
  void compile(const fs::path& _source,
    const fs::path& _destination) override {
    int width, height, channels;

    unsigned char* image =
      stbi_load(_source.string().c_str(), &width, &height, &channels, 0);
    if (image == nullptr) {
      spdlog::error("Cannot load image by path {}", _source.string());
      return;
    }

    std::ofstream output(_destination, std::ios_base::binary);
    if (!output.is_open()) {
      spdlog::error("Cannot create output file: {}", _destination.string());
      return;
    }

    output.write(reinterpret_cast<char*>(&m_id), sizeof(asset_id));

    output.write(reinterpret_cast<char*>(&width), sizeof(int));
    output.write(reinterpret_cast<char*>(&height), sizeof(int));
    output.write(reinterpret_cast<char*>(&channels), sizeof(int));

    const size_t fileSize = width * height * channels + 1;

    size_t zippedSize = compressBound(fileSize);
    char zipped[zippedSize];

    auto result = compress(reinterpret_cast<Bytef*>(zipped), &zippedSize, reinterpret_cast<const Bytef*>(image), fileSize);
    if (result != Z_OK) {
      spdlog::error("Cannot compress data");
      return;
    }

    output.write(zipped, zippedSize);

    output.close();
  }
#endif

  void* load(std::ifstream& file) override {
    return nullptr;
  }

  ImagePipe()
      : AssetPipe("image"){};
};

} // namespace assets
} // namespace wind
#pragma once
#include "pipe.hpp"

#include <filesystem>
#include <spdlog/spdlog.h>

#ifdef WIND_PIPE_WRITE

#include <stb_image.h>

#endif

namespace wind {
namespace assets {

struct Image {
  unsigned char* pixels;
  glm::ivec2 size;
};

class ImagePipe : public AssetPipe {
public:
#ifdef WIND_PIPE_WRITE
  void compile(const fs::path& _source, const fs::path& _destination) override {
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

    const uLong fileSize = width * height * channels + 1;

    uLongf zippedSize = compressBound(fileSize);
    char* zipped = new char[zippedSize];

    auto result = compress(reinterpret_cast<Bytef*>(zipped), &zippedSize, reinterpret_cast<const Bytef*>(image), fileSize);
    if (result != Z_OK) {
      spdlog::error("Cannot compress data");
      return;
    }

    output.write(reinterpret_cast<char*>(&m_id), sizeof(m_id));
    output.write(reinterpret_cast<char*>(&width), sizeof(width));
    output.write(reinterpret_cast<char*>(&height), sizeof(height));
    output.write(reinterpret_cast<char*>(&channels), sizeof(channels));
    output.write(reinterpret_cast<char*>(&zippedSize), sizeof(zippedSize));

    output.write(zipped, zippedSize);

    output.close();
  }
#endif

  void* load(std::ifstream& file) override {
    int width, height, channels;
    uLongf orgSize, zippedSize;

    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));
    file.read(reinterpret_cast<char*>(&channels), sizeof(channels));
    file.read(reinterpret_cast<char*>(&zippedSize), sizeof(zippedSize));

    orgSize = width * height * channels + 1;

    auto zipData = new Bytef[zippedSize];
    file.read(reinterpret_cast<char*>(zipData), zippedSize);

    auto unzipData = new Bytef[orgSize];

    auto rc = uncompress(unzipData, &orgSize, zipData, static_cast<uLongf>(zippedSize));
    if (rc != Z_OK)
      throw std::invalid_argument(fmt::format("Failed uncompress data: {}", zError(rc)));

    delete[] zipData;

    return (void*)(new Image{
      unzipData,
      glm::ivec2{width, height}});
  }

  ImagePipe()
      : AssetPipe("image"){};
};

} // namespace assets
} // namespace wind

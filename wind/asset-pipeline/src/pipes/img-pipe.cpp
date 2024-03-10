#include <asset-pipeline/pipes/img-pipe.h>
#include <filesystem>
#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace wind {
namespace asset_pipeline {

void ImgPipe::compile(const fs::path& _source, const fs::path& _destination) {
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

  auto name = _source.c_str();

  output.write(name, strlen(name) + 1);
  output.write(m_id, strlen(m_id) + 1);

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

} // namespace asset_pipeline
} // namespace wind
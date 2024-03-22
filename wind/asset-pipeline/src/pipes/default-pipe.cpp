#include <asset-pipeline/pipes/default-pipe.h>

namespace wind {
namespace asset_pipeline {

void DefaultPipe::compile(const fs::path& _source, const fs::path& _destination) {
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

  output.write(reinterpret_cast<char*>(m_id), sizeof(asset_id));

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

  output.write(reinterpret_cast<char*>((asset_id)fileContent.size()), sizeof(asset_id));
  output.write(zipped, zippedSize);

  input.close();
  output.close();

  delete[] zipped;
}

Asset* DefaultPipe::load(unsigned char* bytes) {
  //   auto result = uncompress(reinterpret_cast<Bytef*>(zipped), &zippedSize, reinterpret_cast<const Bytef*>(fileContent.c_str()), fileContent.size());
  // if (result != Z_OK) {
  //   spdlog::error("Cannot compress data");
  //   return;
  // }
}

} // namespace asset_pipeline
} // namespace wind
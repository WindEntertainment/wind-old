#include <asset-pipeline/pipes/default-pipe.h>
#include <exception>

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

  auto name = _source.c_str();

  output.write(name, strlen(name) + 1);
  output.write(m_id, strlen(m_id) + 1);

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

  output.write(zipped, zippedSize);

  input.close();
  output.close();

  delete[] zipped;
}

} // namespace asset_pipeline
} // namespace wind
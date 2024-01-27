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

    auto name = _source.relative_path().c_str();

    output.write(name, strlen(name) + 1);
    output.write(m_id, strlen(m_id) + 1);

    const char* fileContent;
    {
        std::stringstream buffer;
        buffer << input.rdbuf();
        fileContent = buffer.str().c_str();
    }
    const size_t fileSize = strlen(fileContent) + 1;

    size_t bufferSize = compressBound(fileSize);
    char buffer[bufferSize];

    auto result = compress(reinterpret_cast<Bytef*>(buffer), &bufferSize,
                           reinterpret_cast<const Bytef*>(fileContent), fileSize);
    if (result != Z_OK) {
        spdlog::error("Cannot compress data");
        return;
    }

    output.write(buffer, bufferSize);
}

}  // namespace asset_pipeline
}  // namespace wind
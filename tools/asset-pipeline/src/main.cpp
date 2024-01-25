#include <asset-pipeline/pipes-register.h>
#include <spdlog/spdlog.h>
#include <zlib.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <ios>
#include <sstream>

namespace wind {

class TxtPipe : public asset_pipeline::Pipe {
private:
    const char* c_id = "TxtPipe";

public:
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

        auto name = _source.relative_path().c_str();

        output.write(c_id, strlen(c_id) + 1);
        output.write(name, strlen(name) + 1);

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
};

int main(int argc, char** argv) {
    const fs::path source = argc > 1 ? argv[1] : fs::current_path() / "asset/";
    const fs::path destination = argc > 2 ? argv[2] : fs::current_path() / "default.bundle";
    const fs::path cache = argc > 3 ? argv[3] : fs::current_path() / ".cache/";

    spdlog::info("Source directory: {}", source.string());
    spdlog::info("Destination bundle path: {}", destination.string());
    spdlog::info("Cache directory: {}", cache.string());

    asset_pipeline::PipeRegister::regPipe(".*\\.txt", new TxtPipe());

    wind::asset_pipeline::AssetPipeline pipeline;
    pipeline.compileDirectory(source, source, cache);

    return EXIT_SUCCESS;
}

}  // namespace wind

int main(int argc, char** argv) {
    return wind::main(argc, argv);
}
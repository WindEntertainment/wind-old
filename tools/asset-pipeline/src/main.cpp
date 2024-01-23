#include <asset-pipeline/pipes-register.h>
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
            spdlog::error("Can't compress data");
            return;
        }

        output.write(buffer, bufferSize);
    }
};

int main(int argc, char** argv) {
    const fs::path source = argc > 1 ? argv[1] : fs::current_path() / "asset/";
    const fs::path destination = argc > 2 ? argv[2] : source.parent_path() / "default.bundle";
    const fs::path cache = argc > 3 ? argv[3] : source.parent_path() / ".cache/";

    spdlog::info("source directory: {}", source.string());
    spdlog::info("destination bunle path: {}", destination.string());
    spdlog::info("cache directory: {}", cache.string());

    asset_pipeline::PipeRegister::regPipe(".*\\.txt", new TxtPipe());

    wind::asset_pipeline::AssetPipeline pipeline;
    pipeline.compileDirectory(source, source, cache);

    return EXIT_SUCCESS;
}

}  // namespace wind

int main(int argc, char** argv) {
    return wind::main(argc, argv);
}
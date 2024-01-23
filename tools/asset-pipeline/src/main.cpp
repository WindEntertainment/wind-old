#include <asset-pipeline/asset-pipeline.h>

#include <filesystem>

namespace wind {

int main(int argc, char** argv) {
    const fs::path source = argc > 1 ? argv[1] : fs::current_path() / "asset/";
    const fs::path destination = argc > 2 ? argv[2] : source.parent_path() / "default.bundle";
    const fs::path cache = argc > 3 ? argv[3] : source.parent_path() / ".cache/";

    spdlog::info("source directory: {}", source.string());
    spdlog::info("destination bunle path: {}", destination.string());
    spdlog::info("cache directory: {}", cache.string());

    wind::asset_pipeline::AssetPipeline pipeline;
    pipeline.compileDirectory(source, source, cache);

    return EXIT_SUCCESS;
}

}  // namespace wind

int main(int argc, char** argv) {
    return wind::main(argc, argv);
}
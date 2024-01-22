#include <asset-pipeline/asset-pipeline.h>

#include <filesystem>

namespace wind {

int main(int argc, char** argv) {
    const fs::path path = argc > 1 ? argv[1] : fs::current_path();
    spdlog::info("work directory: {}", path.string());

    wind::asset_pipeline::AssetPipeline pipeline;
    pipeline.load(path);

    return EXIT_SUCCESS;
}

}  // namespace wind

int main(int argc, char** argv) {
    return wind::main(argc, argv);
}
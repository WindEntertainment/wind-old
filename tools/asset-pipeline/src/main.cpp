#include <asset-pipeline/asset-pipeline.h>

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : argv[0];
    spdlog::info("work directory: {}", path);

    wind::asset_pipeline::AssetPipeline pipeline;
    pipeline.load(path);

    return EXIT_SUCCESS;
}
#include <asset-pipeline/asset_pipeline.h>
#include <wind.h>

int main(int argc, char** argv) {
    wind::asset_pipeline::AssetPipeline pipeline;
    pipeline.load("./asset/.import-config");
    return 0;
}
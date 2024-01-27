#include <asset-pipeline/pipes/content-3d-pipe.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <spdlog/spdlog.h>

#include <assimp/Importer.hpp>

namespace wind {
namespace asset_pipeline {

void Content3DPipe::run(const fs::path& _source, const fs::path& _destination) {
    // load
    const struct aiScene* scene = importer.ReadFile(_source.string().c_str(), m_config.flags);
}

}  // namespace asset_pipeline
}  // namespace wind
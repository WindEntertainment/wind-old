#include <asset-pipeline/pipes/content-3d-pipe.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/node/node.h>

#include <assimp/Importer.hpp>

namespace wind {
namespace asset_pipeline {

void Content3DPipe::compile(const fs::path& _source, const fs::path& _destination) {
    const struct aiScene* scene = importer.ReadFile(_source.string().c_str(), m_config.flags);
}

static std::map<string, int> c_aiFlags = {
    {"aiProcess_Triangulate", aiProcess_Triangulate},
    {"aiProcess_FlipUVs", aiProcess_FlipUVs},
    {"aiProcess_CalcTangentSpace", aiProcess_CalcTangentSpace}};

void Content3DPipe::config(YAML::Node&& _config) {
    auto flags = _config["flags"];

    if (!flags || !flags.IsSequence())
        return;

    m_config.flags = 0;
    for (auto flag : flags) {
        auto key = flag.as<string>();
        if (!c_aiFlags.contains(key)) {
            spdlog::warn("{}: Unknown flag: {}", _config["file"].as<string>(), key);
            continue;
        }

        m_config.flags |= c_aiFlags[key];
    }
}

}  // namespace asset_pipeline
}  // namespace wind
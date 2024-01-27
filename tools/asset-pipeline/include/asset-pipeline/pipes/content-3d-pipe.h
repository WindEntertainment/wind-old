#include <asset-pipeline/pipe.h>
#include <asset-pipeline/raw-pipe.h>
#include <assimp/postprocess.h>

#include <assimp/Importer.hpp>

namespace wind {
namespace asset_pipeline {

class Content3DPipe : public RawPipe {
public:
    void run(const fs::path& _source, const fs::path& _destination) override;

private:
    const char* m_id = "Content3DPipe";
    Assimp::Importer importer;

    struct Config {
        int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;
    } m_config;
};

}  // namespace asset_pipeline
}  // namespace wind
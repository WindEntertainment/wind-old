#include <asset-pipeline/pipe.h>
#include <assimp/postprocess.h>

#include <assimp/Importer.hpp>

namespace wind {
namespace asset_pipeline {

class Content3DPipe : public Pipe {
public:
    void compile(const fs::path& _source, const fs::path& _destination) override;

    Content3DPipe() : Pipe("3d"){};

protected:
    void config(YAML::Node&& config) override;

private:
    Assimp::Importer importer;

    struct Config {
        int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;
    } m_config;
};

}  // namespace asset_pipeline
}  // namespace wind
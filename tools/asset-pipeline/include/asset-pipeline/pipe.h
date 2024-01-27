#pragma once
#include <utils/utils.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>

namespace wind {
namespace asset_pipeline {

class Pipe {
private:
    friend class AssetPipeline;

protected:
    const char* m_id;

    virtual void config(YAML::Node config){};

public:
    virtual void compile(const fs::path& _source, const fs::path& _destination) = 0;

    Pipe(const char* id) : m_id(id){};
};

}  // namespace asset_pipeline
}  // namespace wind
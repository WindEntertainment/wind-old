#pragma once
#include <asset-pipeline/pipe.h>

namespace wind {
namespace asset_pipeline {

class DefaultPipe : public Pipe {
public:
    virtual void compile(const fs::path& source, const fs::path& destination) override;

    DefaultPipe() : Pipe("DefaultPipe"){};
};

}  // namespace asset_pipeline
}  // namespace wind
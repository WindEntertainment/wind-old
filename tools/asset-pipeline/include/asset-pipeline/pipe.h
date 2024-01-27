#pragma once
#include <utils/utils.h>
#include <zlib.h>

namespace wind {
namespace asset_pipeline {

class Pipe {
public:
    virtual void compile(const fs::path& _source, const fs::path& _destination) = 0;
};

}  // namespace asset_pipeline
}  // namespace wind
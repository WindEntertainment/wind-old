#pragma once
#include "asset-bundler/loaders/iloader.h"
#include "asset-bundler/objects/shader.h"

namespace wind {
    namespace assets {
        class ShaderLoader : public ILoader {
        public:
            ISerializable* load(fs::path path) override;
        };
    }
}
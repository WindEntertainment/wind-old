#pragma once
#include "asset-bundler/objects/iserializable.h"

namespace wind {
    namespace assets {
        struct Shader : public ISerializable {
            void _serialize(std::ofstream& os) override;
            void _deserialize(std::ifstream& is) override;

            string vtx, fgt;
        };
    }
}
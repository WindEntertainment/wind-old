#pragma once
#include "asset-bundler/objects/iserializable.h"

namespace wind {
    namespace assets {
        struct Text : public ISerializable {
            string text;
            
            void _serialize(std::ofstream& os) override;
            void _deserialize(std::ifstream& is) override;
        };
    }
}
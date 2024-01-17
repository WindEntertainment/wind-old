#pragma once
#include "asset-bundler/objects/iserializable.h"

namespace wind {
    namespace assets {
        class ILoader {
        public:
            virtual ~ILoader() = default;
            virtual ISerializable* load(fs::path path) = 0;
        };
    }
}
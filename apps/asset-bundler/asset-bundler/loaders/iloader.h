#pragma once
#include "asset-bundler/objects/iserializable.h"

namespace wind {
    namespace assets {
        class ILoader {
        public:
            virtual ISerializable* load(const char* path) = 0;
        };
    }
}
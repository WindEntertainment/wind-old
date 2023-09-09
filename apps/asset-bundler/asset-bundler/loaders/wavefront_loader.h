#include "asset-bundler/objects/mesh.h"
#include "asset-bundler/loaders/iloader.h"

namespace wind {
    namespace assets {
        class WaveFrontObjLoader : public ILoader {
            ISerializable* load(const char* path) override {
                return nullptr;
            }
        };
    }
}
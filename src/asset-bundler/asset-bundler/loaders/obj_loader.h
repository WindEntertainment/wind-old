#include "asset-bundler/objects/mesh.h"
#include "asset-bundler/loaders/iloader.h"

namespace wind {
    namespace assets {
        class ObjLoader : public ILoader {
        public:
            ISerializable* load(fs::path path) override;
        };
    }
} 
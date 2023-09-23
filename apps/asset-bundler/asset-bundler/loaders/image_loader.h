#include "asset-bundler/loaders/iloader.h"
#include "asset-bundler/objects/image.h"

namespace wind {
    namespace assets {
        class ImageLoader : public ILoader {
        public:
            ISerializable* load(fs::path path) override;
        };
    }
}
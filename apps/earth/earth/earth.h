#include <asset-bundler/asset_bundler.h>
#include <asset-bundler/loaders/obj_loader.h>
#include <asset-bundler/loaders/shader_loader.h>
#include <asset-bundler/loaders/image_loader.h>
#include <asset-bundler/loaders/text_loader.h>

namespace earth {
    class Application {
    public:
        void build(const string&& path);
    };
}
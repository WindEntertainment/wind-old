#include "resource_manager.h"

namespace wind {
    namespace resources {
        vector<assets::Bundle*> _internal::bundles{};

        void addBundle(assets::Bundle* _bundle) {
            if (!_bundle || !_bundle->isOpen()) {
                log().error() << "Resources: Can't add NULL bundle";
                return;
            }

            _internal::bundles.push_back(_bundle);
        }
    }
}
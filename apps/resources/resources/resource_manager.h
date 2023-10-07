#pragma once
#include <asset-bundler/bundle.h>

namespace wind {
    namespace resources {
        class _internal {
        public:
            static vector<assets::Bundle*> bundles;
        };

        void addBundle(assets::Bundle*);

        //===================================================//

        template <typename T>
        T* get(const char* name);

        template <typename T>
        T* get(const char* _name) {
            log().error() << "Not found function for load type: [" << typeid(T).name() << "] resource name: [" << _name << "]"; 
            return nullptr;
        }

        //===================================================//
    }
}

#include "getters/asset.h"
#include "getters/texture.h"
#include "getters/shader.h"
#include "getters/mesh.h"
#include "getters/prefab.h"
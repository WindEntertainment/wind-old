#pragma once
#include <asset-bundler/bundle.h>

namespace wind {
    namespace resources {
        template <typename T>
        requires requires (T* t) {
            {t} -> std::convertible_to<assets::ISerializable*>;
        }
        T* get(const char* _name) {
            for (auto bundle : _internal::bundles)
                if (auto res = bundle->getResource<T>(_name))
                    return res;

            return nullptr;
        }
    }
}
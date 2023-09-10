#include "asset-bundler/objects/iserializable.h"

namespace wind {
    namespace assets {
        class Bundle {
        private:
            std::ifstream m_file;
        public:
            void load(const string&& path);

            template <typename T>
            T* getResource(const string&& id) {
                T* res = new T();
                res->deserialize(m_file);
                return res;
            }
        };
    }
}
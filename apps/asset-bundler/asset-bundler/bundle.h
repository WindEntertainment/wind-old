#include "asset-bundler/objects/iserializable.h"

namespace wind {
    namespace assets {
        class Bundle {
        private:
            std::ifstream m_file;
            map<asset_id, size_t> m_offsets;
        public:
            ~Bundle();
            Bundle() {};
            Bundle(const string&& path);

            void load(const string&& path);
            bool isOpen() const;

            template <typename T>
            T* getResource(const string&& _str_id) {
                auto id = getAssetIdByName(_str_id);
                if (!m_offsets.contains(id)) {
                    log().error() 
                        << "Bundle: can't find resource by name: '" 
                        << _str_id << "' id:" << id;
                    return nullptr;
                }

                m_file.seekg(m_offsets[id], std::ios_base::beg);
            
                T* res = new T();
                res->deserialize(m_file);
                return res;
            }
        };
    }
}
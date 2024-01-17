#include "bundle.h"

namespace wind {
    namespace assets {
        bool Bundle::isOpen() const {
            return m_file.is_open();
        }

        void Bundle::load(const string&& _path) {
            log().info() << "Asset Bundle: start loading bundle";
            
            m_file = std::ifstream(_path);
            if (!m_file.is_open()) {
                log().error() << "Asset Bundle: can't open bundle file: [" << _path << "]";
                return;
            }

            try {
                auto num_assets = read<size_t>(m_file);
                for (size_t i = 0; i < num_assets; ++i) {
                    auto id = read<asset_id>(m_file);
                    auto offset = read<size_t>(m_file);

                    m_offsets.insert(std::make_pair(
                        id, offset 
                    ));
                }
       
                log().info() 
                    << "Asset Bundle: finish loaded bundle header. Assets count in bundle: "
                    << num_assets;
            } catch (std::invalid_argument& ex) {
                log().error() << ex.what();
            }
        }

        Bundle::Bundle(const string&& path) {
            load(std::move(path));
        }

        Bundle::~Bundle() {
            m_file.close();
        }
    }
}
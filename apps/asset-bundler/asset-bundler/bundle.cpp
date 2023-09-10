#include "bundle.h"

namespace wind {
    namespace assets {
        void Bundle::load(const string&& _path) {
            log().info() << "Asset Bundle: start loading bundle";
            
            m_file = std::ifstream(_path);
            if (!m_file.is_open()) {
                log().error() << "Asset Bundle: can't open bundle file:" << _path;
                return;
            }

            
        }
    }
}
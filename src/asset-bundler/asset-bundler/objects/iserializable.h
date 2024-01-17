#pragma once
#include "asset-bundler/utils.h"

namespace wind {
    namespace assets {       
        struct ISerializable {
        public:
            asset_id id = 0;

            void serialize(std::ofstream& os) {
                _serialize(os);
            }

            void deserialize(std::ifstream& is) {
                _deserialize(is);
            }

            virtual ~ISerializable() = default;
        protected:
            virtual void _serialize(std::ofstream& os) = 0;
            virtual void _deserialize(std::ifstream& is) = 0;
        };
    }
}
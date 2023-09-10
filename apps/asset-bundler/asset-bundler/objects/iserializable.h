#pragma once
#include <logger/wind_logger.h>

namespace wind {
    namespace assets {       
        template<typename T>
        inline void write(std::ofstream& os, T data) {
            os.write(reinterpret_cast<char*>(&data), sizeof(data));
        }

        template<typename T>
        inline T read(std::ifstream& is) {
            T value;
            is.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;   
        }

        using asset_id = unsigned long;

        asset_id getAssetIdByName(const std::string &str);

        struct ISerializable {
        public:
            asset_id id = 0;

            void serialize(std::ofstream& os) {
                _serialize(os);
            }

            void deserialize(std::ifstream& is) {
                _deserialize(is);
            }
        protected:
            virtual void _serialize(std::ofstream& os) = 0;
            virtual void _deserialize(std::ifstream& is) = 0;
        };

    }
}
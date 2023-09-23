#pragma once
#include <logger/wind_logger.h>

namespace wind {
    namespace assets {
        using asset_id = unsigned long;
        asset_id getAssetIdByName(const std::string &str);
        
        template<typename T>
        inline void write(std::ofstream& os, T data) {
            os.write(reinterpret_cast<char*>(&data), sizeof(data));
        }

        template<typename T>
        inline T read(std::ifstream& is) {
            if (!is.good())
                throw std::invalid_argument("end of file");
            T value;
            is.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;   
        }
    }
}
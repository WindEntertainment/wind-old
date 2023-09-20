#pragma once
#include <logger/wind_logger.h>

namespace wind {
    namespace assets {
        using asset_id = unsigned long;
        asset_id getAssetIdByName(const std::string &str);

        [[nodiscard]] inline std::string narrow(const wchar_t* str) {
            const auto length = wcslen(str);

            std::string result;
            result.resize(length);

            const auto& facet = use_facet<std::ctype<wchar_t>>(std::ostringstream().getloc());
            std::transform(str, str + length, result.begin(), [&facet](const wchar_t ch) {
                return facet.narrow(ch);
            });
            
            return result;
        }

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
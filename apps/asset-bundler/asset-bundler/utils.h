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
            // is.fail or is.flags for get error?? 
            return value;   
        }

        class Stopwatch {
        private:
            typedef std::chrono::steady_clock clock;
            std::chrono::time_point<clock> start_time;
        public:
            Stopwatch():
                start_time(clock::now()) {}

            void reset() {
                start_time = clock::now();
            }

            clock::duration elapsed() {
                return clock::now() - start_time;
            }

            int64_t ms() {
                return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed()).count();
            }
        };
    }
}
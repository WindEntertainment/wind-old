#pragma once
#include <logger/wind_logger.h>

namespace wind {
    namespace assets {
        struct ISerializable {
        public:
            string id = "";

            void serialize(std::ofstream& os) {
                os << id;
                _serialize(os);
            }
        protected:
            virtual void _serialize(std::ofstream& os) = 0;

            template<typename T>
            void write(std::ofstream& os, T data) {
                os.write(reinterpret_cast<char*>(&data), sizeof(data));
            }
        };
    }
}
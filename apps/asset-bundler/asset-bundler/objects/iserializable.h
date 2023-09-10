#pragma once
#include <logger/wind_logger.h>

namespace wind {
    namespace assets {
        struct ISerializable {
        public:
            string id = "";

            void serialize(std::ofstream& os) {
                os << id << '\0';
                _serialize(os);
            }

            void deserialize(std::ifstream& is) {
                char ch;
                do {
                    ch = read<char>(is);
                    id += ch;
                } while (ch != '\0');
                
                _deserialize(is);
            }
        protected:
            virtual void _serialize(std::ofstream& os) = 0;
        
            template<typename T>
            inline void write(std::ofstream& os, T data) const {
                os.write(reinterpret_cast<char*>(&data), sizeof(data));
            }

            virtual void _deserialize(std::ifstream& is) = 0;

            template<typename T>
            inline T read(std::ifstream& is) const {
                T value;
                is.read(reinterpret_cast<char*>(&value), sizeof(value));
                return value;   
            }
        };

    }
}
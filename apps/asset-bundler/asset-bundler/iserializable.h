#include <logger/wind_logger.h>

namespace wind {
    namespace assets {
        struct ISerializable {
            virtual void serialize(std::ofstream& os) = 0;
        protected:
            template<typename T>
            void write(std::ofstream& os, T data) {
                os.write(reinterpret_cast<const char*>(data), sizeof(data));
            }
        };
    }
}
#include "iserializable.h"

namespace wind {
    namespace assets {
        class ILoader {
        public:
            ISerializable* load(const char* path);
        };
    }
}
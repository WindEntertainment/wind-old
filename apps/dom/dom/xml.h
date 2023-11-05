#include "document.h"

namespace wind {
    namespace dom {
        class XML {
        public:
            static Document* LoadFile(const char* path);
        };
    }
}
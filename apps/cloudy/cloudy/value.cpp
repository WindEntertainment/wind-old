#include "document.h"

namespace wind {
    namespace cloudy {
        Object* Value::copy(Document* allocator) {
            return allocator->allocValue(m_value);
        }
    }
}
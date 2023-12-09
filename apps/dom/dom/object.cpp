#include "document.h"

namespace wind {
    namespace doom {
        Object* Value::copy(Document* allocator) {
            return allocator->allocValue(m_value);
        }

        Object* Container::copy(Document* allocator) {
            auto container = allocator->allocContainer();
            for (auto obj : m_objs)
                container->addObject(obj.first, obj.second->copy(allocator));
            return container;
        }
    }
}
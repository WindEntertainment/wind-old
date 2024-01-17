#include "document.h"

namespace wind {
    namespace cloudy {
        void Container::addObject(string key, Object* object) {
            if (object->allocator() != allocator()) {
                log().error() << "Container::addObject(): it's not possible to add an object using another allocator. key: " << key;
                return;
            }

            m_objs.insert(std::make_pair(
                key, object
            ));
        }

        Object* Container::copy(Document* allocator) {
            auto container = allocator->allocContainer();
            for (auto obj : m_objs)
                container->addObject(obj.first, obj.second->copy(allocator));
            return container;
        }
    }
}
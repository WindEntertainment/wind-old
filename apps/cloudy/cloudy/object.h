#pragma once
#include "utils.h"

namespace wind {
    namespace cloudy {
        enum class TypeObject {
            NIL,
            VALUE,
            CONTAINER
        };

        class Document;

        class Container;
        class Value; 

        class Object {
            friend class Document;
        private:
            TypeObject m_type = TypeObject::NIL;
            Document* m_allocator = nullptr;
        protected:
            Object(TypeObject type, Document* allocator):
                m_type(type), m_allocator(allocator) {};
        public:
            virtual Object* copy(Document*) = 0;
            
            inline Document* allocator() const {
                return m_allocator;
            }

            inline TypeObject getType() const {
                return m_type;
            }

            inline bool isContainer() const {
                return m_type == TypeObject::CONTAINER;
            }

            inline bool isValue() const {
                return m_type == TypeObject::VALUE;
            }

            inline Container* asContainer() const {
                if (m_type != TypeObject::CONTAINER)
                    return nullptr;
                return (Container*)this;
            }

            inline Value* asValue() const {
                if (m_type != TypeObject::VALUE)
                    return nullptr;
                return (Value*)this;
            }
        };  
    }
}
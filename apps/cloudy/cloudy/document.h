#pragma once
#include "container.h"
#include "value.h"

namespace wind {
    namespace cloudy {
        class Document final {
        private:
            std::list<Object*> m_pool; 
            Container* m_root;
        public:
            Document();
            ~Document();

            Value* allocValue(string _value);
            Container* allocContainer();

            inline Container* root() const {
                return m_root;
            }           
        };
    }
}
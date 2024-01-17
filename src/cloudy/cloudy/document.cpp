#include "document.h"

namespace wind {
    namespace cloudy {
        Document::Document() {
            m_root = allocContainer();
        }

        Document::~Document() {
            for (auto obj : m_pool)
                delete obj;
            m_pool.clear();
        }

        Value* Document::allocValue(string _value) {
            auto obj = new Value(_value, this);
            m_pool.push_back(obj);
            return obj;
        }

        Container* Document::allocContainer() {
            auto container = new Container(this);
            m_pool.push_back(container);
            return container;
        }     
    }
}
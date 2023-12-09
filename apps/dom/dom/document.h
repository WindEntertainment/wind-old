/*

    {
        "field1": "value1",
        "field2": {
            "child-field1": "child-value1"
        },
        "field3": [
            1, 2, 3, 4, 5
        ]
    }

    <>
        <field1>value1</field1>
        <field2>
            <child-field1>child-value1</child-field1>
        </field2>
        <field3>
            <el>1</el>
            <el>2</el>
            <el>3</el>
            <el>4</el>
            <el>5</el>
        </field3>
    </>

    Document:
        "field1" = StringObject("value1")
        "field2" = ContainerObject {
            "child-field1" = StringObject("child-value1")
        }
        "field3" = ContainerObject {
            el_1 = 1
            el_2 = 2
            el_3 = 3
            el_4 = 4
            el_5 = 5
        }
*/

#include "object.h"

namespace wind {
    namespace doom {
        class Document final {
        private:
            std::list<Object*> m_pool; 

            Container* m_root;
        public:
            Document() {
                m_root = allocContainer();
            }

            ~Document() {
                for (auto obj : m_pool)
                    delete obj;
                m_pool.clear();
            }

            Value* allocValue(string _value) {
                auto obj = new Value(_value);
                m_pool.push_back(obj);
                return obj;
            }

            Container* allocContainer() {
                auto container = new Container();
                m_pool.push_back(container);
                return container;
            }

            inline Container* root() const {
                return m_root;
            }         
        };
    }
}
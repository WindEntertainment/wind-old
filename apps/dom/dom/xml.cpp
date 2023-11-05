#include "xml.h"
#include <tinyxml2.h>

namespace wind {
    namespace dom {
        Document* XML::LoadFile(const char* _path) {
            using namespace tinyxml2;

            XMLDocument xdoc;
            auto res = xdoc.LoadFile(_path);
            if (res != XMLError::XML_SUCCESS) {
                log().error() << "XML::DeserializationFile by path '" << _path << "': " << xdoc.ErrorIDToName(res);
                return nullptr;
            }

            Document* doc = new Document();
            std::function<void(XMLElement*, Container*)> tree_recursion = [&](XMLElement* parent, Container* container) {
                for (
                    auto node = parent;
                    node != nullptr;
                    node = node->NextSiblingElement()
                ) {
                    if (auto child = node->FirstChildElement()) {
                        auto child_container = doc->allocContainer();
                        container->addObject(node->Name(), child_container);

                        tree_recursion(child, child_container);
                    } else {
                        auto text = node->GetText();
                        auto value = doc->allocValue(text ? text : "");
                        container->addObject(node->Name(), value);
                    }
                }
            };
            tree_recursion(xdoc.RootElement(), doc->root());

            return doc;
        }
    }
}
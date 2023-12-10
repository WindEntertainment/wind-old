#include "xml.h"
#include <tinyxml2.h>

namespace wind {
    namespace cloudy {
        using namespace tinyxml2;

        void BuildDOM(Document* dst, XMLDocument& src) {
            std::function<void(XMLElement*, Container*)> tree_recursion = [&](XMLElement* parent, Container* container) {
                for (
                    auto node = parent;
                    node != nullptr;
                    node = node->NextSiblingElement()
                ) {
                    if (auto child = node->FirstChildElement()) {
                        string name = node->Name();
                        if (container->hasMember(name))
                            name = name + std::to_string(container->size());

                        auto child_container = dst->allocContainer();
                        container->addObject(name, child_container);

                        tree_recursion(child, child_container);
                    } else {
                        auto text = node->GetText();
                        auto value = dst->allocValue(text ? text : "");
                        container->addObject(node->Name(), value);
                    }
                }
            };
            tree_recursion(src.RootElement(), dst->root());
        }

        Document* XML::LoadFile(const char* _path) {
            XMLDocument xdoc;
            auto res = xdoc.LoadFile(_path);
            if (res != XMLError::XML_SUCCESS) {
                log().error() << "XML::LoadFile by path '" << _path << "': " << xdoc.ErrorIDToName(res);
                return nullptr;
            }

            Document* doc = new Document();
            BuildDOM(doc, xdoc);

            return doc;
        }

        Document* XML::LoadRAW(const char* _raw, size_t _nbytes) {
            XMLDocument xdoc;
            auto res = xdoc.Parse(_raw, _nbytes);
            if (res != XMLError::XML_SUCCESS) {
                log().error() << "XML::LoadRaw error:" << xdoc.ErrorIDToName(res) << ";\n" << _raw;
                return nullptr;
            }

            Document* doc = new Document();
            BuildDOM(doc, xdoc);

            return doc;
        }
    }
}
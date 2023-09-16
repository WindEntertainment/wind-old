#include "asset-bundler/loaders/shader_loader.h"
#include <tinyxml2.h>

namespace wind {
    namespace assets {
        ISerializable* ShaderLoader::load(const char* _path) {
            namespace xml = tinyxml2;
            
            xml::XMLDocument doc;
            xml::XMLError err = doc.LoadFile(_path);
            if (err != xml::XML_SUCCESS) {
                log().error() << "[" << _path << "] XMLError: " << doc.ErrorIDToName(err);
                return nullptr;
            }

            Shader* shader = new Shader();

            shader->vtx = doc.FirstChildElement("vtx")->GetText();
            shader->fgt = doc.FirstChildElement("fgt")->GetText();

            return shader;
        }
    }
}
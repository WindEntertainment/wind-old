#include "text_loader.h"

namespace wind {
    namespace assets {
        ISerializable* TextLoader::load(fs::path path) {
            std::ifstream file(path);
            if (!file.is_open()) {
                log().error() << "TextLoader: failed open file: [" << path.string().c_str() << "]";
                return nullptr;
            }

            std::stringstream ss;
            ss << file.rdbuf();

            Text* text = new Text();
            text->text = ss.str();

            return text;
        }
    }
}
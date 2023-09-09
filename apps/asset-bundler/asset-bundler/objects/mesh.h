#include "asset-bundler/objects/iserializable.h"
#include <glm/glm.hpp>

namespace wind {
    namespace assets {
        struct Mesh : public ISerializable {
            void serialize(std::ofstream& os) override {}

            vector<glm::vec2> vertices;
        };
    }
}
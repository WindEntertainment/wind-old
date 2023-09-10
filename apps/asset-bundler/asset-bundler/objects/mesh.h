#include "asset-bundler/objects/iserializable.h"
#include <glm/glm.hpp>


namespace wind {
    namespace assets {
        struct Mesh : public ISerializable {
            void _serialize(std::ofstream& os) override;

            vector<glm::vec3> vertices;
            vector<uint> indices;
        };
    }
}
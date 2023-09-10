#include "mesh.h"

namespace wind {
    namespace assets {

        void Mesh::_serialize(std::ofstream& os) {
            write(os, vertices.size());
            for (auto vertex : vertices) {
                write(os, vertex.x);
                write(os, vertex.y);
                write(os, vertex.z);
            }

            write(os, indices.size());
            for (auto index : indices) 
                write(os, index);
        }
    }
}
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

            write(os, uv.size());
            for (auto tc : uv)
                write(os, tc);
        }

        void Mesh::_deserialize(std::ifstream& is) {
            auto vsize = read<size_t>(is);
            vertices.resize(vsize);
            for (uint i = 0; i < vsize; ++i)
                vertices[i] = {
                    read<float>(is),
                    read<float>(is),
                    read<float>(is),
                };

            auto isize = read<size_t>(is);
            indices.resize(isize);
            for (uint i = 0; i < isize; ++i)
                indices[i] = read<uint>(is);

            auto uvsize = read<size_t>(is);
            uv.resize(uvsize);
            for (uint i = 0; i < uvsize; ++i)
                uv[i] = {
                    read<float>(is),
                    read<float>(is),
                    read<float>(is)
                };
        }
    }
}
#include "shader.h"

namespace wind {
    namespace assets {
        void Shader::_serialize(std::ofstream& os) {
            write(os, vtx.size());
            for (char ch : vtx)
                write(os, ch);

            write(os, fgt.size());
            for (char ch : fgt)
                write(os, ch);
        }

        void Shader::_deserialize(std::ifstream& is) {
            size_t vsize = read<size_t>(is);
            vtx.resize(vsize);
            for (size_t i = 0; i < vsize; ++i) 
                vtx[i] = read<char>(is);

            size_t fsize = read<size_t>(is);
            fgt.resize(fsize);
            for (size_t i = 0; i < fsize; ++i) 
                fgt[i] = read<char>(is);
        }
    }
}
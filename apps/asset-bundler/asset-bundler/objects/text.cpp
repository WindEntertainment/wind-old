#include "text.h"

namespace wind {
    namespace assets {
        void Text::_serialize(std::ofstream& os) {
            write(os, text.size());
            os.write(reinterpret_cast<const char*>(text.c_str()), text.size());
        }

        void Text::_deserialize(std::ifstream& is) {
            auto size = read<size_t>(is);
            text.resize(size);

            is.read(text.data(), size);
        }
    }
}
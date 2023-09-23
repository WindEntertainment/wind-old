#include "image.h"

namespace wind {
    namespace assets {
        void Image::_serialize(std::ofstream& os) {
            write(os, width);
            write(os, height);
            write(os, channels);
            for (int i = 0; i < width * height; ++i)
                write(os, data[i]);
        }


        void Image::_deserialize(std::ifstream& is) {
            width = read<int>(is);
            height = read<int>(is);
            channels = read<int>(is);

            data = new unsigned char[width * height];
            for (int i = 0; i < width * height; ++i)
                data[i] = read<unsigned char>(is);
        }

        Image::~Image() {
            delete[] data;
            width = height = 0;
        }
    }
}
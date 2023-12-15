#include "image.h"

namespace wind {
    namespace assets {
        void Image::_serialize(std::ofstream& os) {
            write(os, width);
            write(os, height);
            write(os, channels);
            
            os.write(reinterpret_cast<char*>(data), width * height * channels + 1);
        }


        void Image::_deserialize(std::ifstream& is) {
            width = read<int>(is);
            height = read<int>(is);
            channels = read<int>(is);

            data = new unsigned char[width * height * channels + 1];
            is.read(reinterpret_cast<char*>(data), width * height * channels + 1);
        }

        Image::~Image() {
            delete[] data;
            width = height = 0;
        }
    }
}
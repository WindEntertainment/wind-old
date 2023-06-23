#include "Resources.h"

namespace app {
    template <typename T>
    T Resources::tryLoad(string _path) {
        LOG(INFO) << "int:" << _path;
        return 5;
    }

    template int Resources::tryLoad<int>(string);
}
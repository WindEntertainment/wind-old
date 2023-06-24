#include "Resources.h"

namespace app {
    template <typename T>
    T Resources::load(string _path) {
        LOG(INFO) << "int:" << _path;
        return 5;
    }

    template int Resources::load<int>(string);
}
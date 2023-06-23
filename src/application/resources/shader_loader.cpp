#include "Resources.h"

namespace app {
    template <typename T>
    T Resources::tryLoad(string _path) {
        LOG(INFO) << "shader:" << _path;
        return Shader();
    }

    template Shader Resources::tryLoad<Shader>(string);
}
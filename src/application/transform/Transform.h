#include "../model/Model.h"

namespace app {
    struct Transform : public Component {
        vec3 position = {};
        vec3 rotation = {};

        Transform(vec3 _position, vec3 _rotation):
            position(_position), rotation(_rotation) {};
    };
}
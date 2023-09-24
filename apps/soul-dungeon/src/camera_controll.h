#include "utils.h"

#include <renderer/renderer.h>

namespace soul_dungeon {
    class CameraControll {
    private:
        float m_yaw,
              m_pitch;
    public:
        float speed;
        float sensitivity;

        CameraControll();
        void update();
    };
}
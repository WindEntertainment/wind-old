#include "utils.h"

#include <renderer/renderer.h>

namespace soul_dungeon {
    class CameraControll {
    private:
        float m_yaw,
              m_pitch;
    public:
        renderer::Camera* camera;

        float speed;
        float sensitivity;

        CameraControll(renderer::Camera*);
        void update();
    };
}
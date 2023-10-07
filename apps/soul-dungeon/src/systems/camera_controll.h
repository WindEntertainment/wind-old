#include <std-game/system.h>
#include <renderer/renderer.h>

namespace soul_dungeon {
    class CameraControll : public wind::stdgame::System {
    private:
        float m_yaw,
              m_pitch;
    public:
        float speed;
        float sensitivity;

        CameraControll();
        void update(entt::registry&) override;
    };
}
// clang-format off
#include <glm/common.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>
#include <renderer/renderer.h>
#include <window/window.h>
#include <utils/utils.h>
// clang-format on

namespace space {

using namespace wind;

struct Particle {
    vec2 position;
    float weight;

    vec2 velocity = {0, 0};
    vec2 acceleration = {0, 0};
};

class ParticleRegister {
private:
    vector<Particle> m_particles;

    static ParticleRegister s_Instance;

public:
    static void spawnParticle(vec2 _position, vec2 velocity, float _weight) {
        s_Instance.m_particles.push_back({
            _position,
            _weight,
            velocity,
        });
    }

    auto begin() {
        return m_particles.begin();
    }

    auto end() {
        return m_particles.end();
    }

    static ParticleRegister& singlton() {
        return s_Instance;
    }
};

ParticleRegister ParticleRegister::s_Instance;

class PhysicsSimulation {
private:
    const float G = 1; // 6.67430e-11f;

public:
    void update() {
        for (auto& i : ParticleRegister::singlton()) {
            i.acceleration = {};

            for (auto& j : ParticleRegister::singlton()) {
                if (&i == &j)
                    continue;

                vec2 diff = j.position - i.position;

                float epsilon = 1e-5;
                float distanceSquared = glm::dot(diff, diff) + epsilon;
                float force = G * j.weight / distanceSquared;

                i.acceleration += force * glm::normalize(diff);
            }
        }

        for (auto& i : ParticleRegister::singlton()) {
            i.velocity += i.acceleration;
            i.position += i.velocity;
        }
    }
};

} // namespace space

int main() {
    using namespace space;

    Window::init([](Window::Config* self) {
        self->title = "Space";
        self->fullScreen = false;
        self->size = {1920, 1080};
    });

    PhysicsSimulation simulation;

    // ParticleRegister::spawnParticle({1250.f, 600.f}, 10.f);
    ParticleRegister::spawnParticle({550.f, 650.f}, {1.0f, 0.5f}, 10.f);
    ParticleRegister::spawnParticle({800.f, 900.f}, {0, 0}, 50.f);

    while (Window::update()) {
        if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            Window::close();

        simulation.update();

        Renderer::clear({0.8f, 0.8f, 0.8f, 1});
        for (auto& particle : ParticleRegister::singlton())
            Renderer::drawCircle(particle.position, particle.weight * 1,
                                 {0.f, 0.5f, 0.f, 1});
        Window::show();
    }

    return EXIT_SUCCESS;
}
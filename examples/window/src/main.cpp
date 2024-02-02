// clang-format off
#include <cstdlib>
#include <glm/common.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>
#include <renderer/renderer.h>
#include <window/window.h>
#include <utils/utils.h>
// clang-format on

namespace space {

using namespace wind;

struct Particle {
    glm::dvec2 position;
    double weight;
    double size;

    glm::dvec2 velocity = {0, 0};
    glm::dvec2 acceleration = {0, 0};
};

class ParticleRegister {
private:
    vector<Particle> m_particles;

    static ParticleRegister s_Instance;

public:
    static void setCapacity(size_t size) {
        s_Instance.m_particles.reserve(size + 1);
    }

    static void spawnParticle(glm::dvec2 _position, double _weight) {
        s_Instance.m_particles.push_back({_position, _weight, 1.f});
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
    const double G = 0.1f;

public:
    void update() {
        for (auto& i : ParticleRegister::singlton()) {
            i.acceleration = {};

            for (auto& j : ParticleRegister::singlton()) {
                if (&i == &j)
                    continue;

                glm::dvec2 diff = j.position - i.position;
                glm::dvec2 normal = glm::normalize(diff);

                double epsilon = 1e-5;
                double distanceSquared = glm::dot(diff, diff) + epsilon;
                double force = G * j.weight / distanceSquared;

                i.acceleration += force * normal;

                if (distanceSquared < pow(i.size + j.size, 2)) {
                    if (j.weight > i.weight) {
                        j.velocity += i.velocity * (i.weight / j.weight);
                        i.velocity = glm::reflect(i.velocity, normal);

                        j.weight += i.weight * 0.1f;
                        i.weight *= 0.9f;
                    }
                }
            }
        }

        for (auto& i : ParticleRegister::singlton()) {
            i.velocity += i.acceleration;
            i.position += i.velocity;

            i.size = glm::clamp(i.weight * 0.3, 1.0, 100.0);
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

    vec2 camera = {};
    const float c_cameraSpeed = 4.f;

    const int numParticles = 2000;

    ParticleRegister::setCapacity(numParticles);
    for (int i = 0; i < numParticles; ++i) {
        glm::dvec2 position{static_cast<double>(-10000 + rand() % 20000),
                            static_cast<double>(-10000 + rand() % 20000)};
        double weight = 1 + rand() % 10;
        ParticleRegister::spawnParticle(position, weight);
    }

    while (Window::update()) {
        if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            Window::close();

        if (Keyboard::isKey(GLFW_KEY_W))
            camera.y -= c_cameraSpeed;
        if (Keyboard::isKey(GLFW_KEY_S))
            camera.y += c_cameraSpeed;
        if (Keyboard::isKey(GLFW_KEY_A))
            camera.x += c_cameraSpeed;
        if (Keyboard::isKey(GLFW_KEY_D))
            camera.x -= c_cameraSpeed;

        simulation.update();

        Renderer::clear({0.8f, 0.8f, 0.8f, 1});
        Renderer::updateCamera(camera);

        for (auto& particle : ParticleRegister::singlton())
            Renderer::drawCircle(particle.position, particle.weight,
                                 {0.f, 0.5f, 0.f, 1});
        Window::show();
    }

    return EXIT_SUCCESS;
}
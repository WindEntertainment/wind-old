// clang-format off
#include <glm/common.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>

#include <renderer/renderer.h>
#include <renderer/particle.h>
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
    const double G = 1.f;

public:
    void update() {
        for (auto& i : ParticleRegister::singlton()) {
            i.acceleration = {};

            for (auto& j : ParticleRegister::singlton()) {
                if (&i == &j)
                    continue;

                glm::dvec2 diff = j.position - i.position;
                glm::dvec2 normal = glm::normalize(diff);

                double distanceSquared = glm::dot(diff, diff);

                if (distanceSquared < pow(i.size + j.size, 2)) {
                    if (j.weight > i.weight) {
                        // clang-format off
                        i.velocity =
                            (i.weight - j.weight) / (i.weight + j.weight) * i.velocity +
                            (2 * j.weight)        / (i.weight + j.weight) * j.velocity;

                        j.velocity =
                            (2 * i.weight)        / (i.weight + j.weight) * i.velocity +
                            (j.weight - i.weight) / (i.weight + j.weight) * j.velocity;

                        // clang-format on

                        // j.weight += i.weight * 0.1f;
                        // i.weight *= 0.9f;
                    }
                } else {
                    double force = G * j.weight / distanceSquared;
                    i.acceleration += force * normal;
                }
            }
        }

        for (auto& i : ParticleRegister::singlton()) {
            i.velocity += i.acceleration;
            i.position += i.velocity;

            i.size = glm::clamp(i.weight * 0.5, 1.0, 500.0);
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
        self->vSync = false;
    });

    // clang-format off
    vector<vec3> vertices;
    vector<unsigned int> indices;
    vector<vec2> uv;

    const int numSegments = 12;
    const float segmentAngle = 2.f * PI / numSegments;

    vertices.push_back({0, 0, 0});
    uv.push_back({0.5f, 0.5f});

    for (int i = 0; i < numSegments; ++i) {
        float angle = i * segmentAngle;
        float c = cosf(angle),
                s = sinf(angle);

        vertices.push_back({ c, s, 0.f });
        uv.push_back({
            0.5f + 0.5f * c,
            0.5f + 0.5f * s
        });
    }

    for (int i = 1; i <= numSegments; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back((i % numSegments) + 1);
    }

    ParticleSystem pSystem{vertices, indices, uv, 2500};
    // clang-format on

    PhysicsSimulation simulation;

    float scope = 1.f;
    vec2 camera = {};

    vec2 mouseDownPosition = {};
    vec2 mouseDownCamera = {};

    const int numParticles = 2500;

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

        if (Mouse::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            mouseDownPosition = Mouse::position();
            mouseDownCamera = camera;
        }

        // clang-format off
        if (Mouse::isButton(GLFW_MOUSE_BUTTON_LEFT))
            camera = {
                mouseDownCamera.x + (Mouse::position().x - mouseDownPosition.x) * scope,
                mouseDownCamera.y - (Mouse::position().y - mouseDownPosition.y) * scope
            };
        // clang-format on

        scope -= scope * 0.05f * Mouse::yScroll();

        simulation.update();

        Renderer::clear({0.1f, 0.1f, 0.1f, 1});

        Renderer::updateCamera(camera);
        Renderer::setScope(scope);

        // for (auto& particle : ParticleRegister::singlton())
        //     Renderer::drawCircle(particle.position, particle.size,
        //                          {0.8f, 0.8f, 0.8f, 1});

        uint i = 0;
        for (auto& particle : ParticleRegister::singlton())
            pSystem.setPosition(i++, particle.position);

        Renderer::drawParticles(&pSystem);

        Window::show();
    }

    return EXIT_SUCCESS;
}
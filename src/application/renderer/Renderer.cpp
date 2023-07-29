#include "Renderer.h"

namespace app {
    bool crossing(vec2 _l1a, vec2 _l1b, vec2 _l2a, vec2 _l2b, vec2& out) {
        vec3 a = vec3(_l1b - _l1a, 0),
             b = vec3(_l2b - _l2a, 0);
        
        vec3 cross1 = glm::cross(a, vec3(_l2a - _l1a, 0)),
             cross2 = glm::cross(a, vec3(_l2b - _l1a, 0));
            
        if (glm::sign(cross1.z) == glm::sign(cross2.z))
            return false;

        vec3 cross3 = glm::cross(b, vec3(_l1a - _l2a, 0)),
             cross4 = glm::cross(b, vec3(_l1b - _l2a, 0));

        if (glm::sign(cross3.z) == glm::sign(cross4.z))
            return false;

        out.x = _l1a.x + a.x * glm::abs(cross3.z) / glm::abs(cross4.z - cross3.z);
        out.y = _l1a.y + a.y * glm::abs(cross3.z) / glm::abs(cross4.z - cross3.z);

        return true;
    }

    Renderer::Renderer(Canvas* _canvas, World* _world):
        m_canvas(_canvas), m_world(_world) {};

    void Renderer::render() {
        const float p4 = PI / 4;

        int i = 0;
        float alpha = m_world->alpha - p4;

        while (alpha < m_world->alpha + p4 && i < 800) {
            float height = raycast(m_world->player, alpha);
            height = 600 / (height * cos(alpha - m_world->alpha));

            m_canvas->wall(i, height);

            alpha += PI/800/2;
            i += 1;
        }

        m_canvas->draw();
    }

    float Renderer::raycast(vec2 _camera, float _alpha) {
        vec2 ray = {
            _camera.x + 10 * glm::cos(_alpha),
            _camera.y + 10 * glm::sin(_alpha)
        };

        float min = FLT_MAX;
        vec2 cross_point;
        for (int i = 0; i < m_world->lines.size(); ++i) {
            vec2 a = m_world->vertex[m_world->lines[i].x],
                 b = m_world->vertex[m_world->lines[i].y];

            if (crossing(a, b, _camera, ray, cross_point)) {
                float dist = glm::distance(cross_point, _camera);
                if (dist < min)
                    min = dist;
            }
        }
        
        return min;
    }
}
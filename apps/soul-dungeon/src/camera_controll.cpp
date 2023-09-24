#include "camera_controll.h"

#include <system/events/mouse.h>
#include <system/events/keyboard.h>

namespace soul_dungeon {
    CameraControll::CameraControll(renderer::Camera* _camera) {
        camera = _camera;

        speed = 3.f;
        sensitivity = 0.5f;
    }

    void CameraControll::update() {
        // ROTATION
        m_yaw   += system::Mouse::offset().x * sensitivity;
        m_pitch += system::Mouse::offset().y * sensitivity;

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        direction.y = sin(glm::radians(m_pitch));
        direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        camera->front = glm::normalize(direction);

        // MOVEMENT
        float ds = speed * system::Application::deltaTime();
        if (system::Keyboard::isKey(GLFW_KEY_W)) 
            camera->position += ds * camera->front;
        if (system::Keyboard::isKey(GLFW_KEY_S))
            camera->position -= ds * camera->front;
        if (system::Keyboard::isKey(GLFW_KEY_A))
            camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * ds;
        if (system::Keyboard::isKey(GLFW_KEY_D))
            camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * ds;
        //
    }
}
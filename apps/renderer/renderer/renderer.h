#pragma once
#include "mesh.h"
#include "camera.h"

namespace wind {
    namespace renderer {
        class Renderer {
        private:
            Camera* m_camera;
        public:
            void setCamera(Camera*);
            Camera* getCamera() const;
            
            void clear();
            void render(Mesh* mesh, vec3 position, vec3 rotation); 
        };
    }
}
#include "mesh.h"

namespace wind {
    namespace renderer {
        Texture* Mesh::texture() const {
            return m_texture;
        }

        Shader* Mesh::shader() const { 
            return m_shader;
        }

        uint Mesh::VAO() const {
            return m_VAO;
        }

        uint Mesh::size() const {
            return m_indices.size(); 
        }

        Mesh::Mesh(vector<vec3> _vertices, vector<uint> _indicies, vector<vec2> _uv, Texture* _texture, Shader* _shader) {
            assert(
                _vertices.size() == _uv.size()
            );
            
            m_vertices.resize(_vertices.size());
            for (uint i = 0; i < m_vertices.size(); ++i)
                m_vertices[i] = {
                    _vertices[i],
                    _uv[i]
                };

            m_indices = _indicies;
            
            
            //====================================//
            
            m_shader = _shader;
            m_texture = _texture;

            m_shader->uInt("ourTexture", 0);

            //====================================//

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_EBO);

            glBindVertexArray(m_VAO);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);        
            glBufferData(
                GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex),
                &m_vertices[0], GL_STATIC_DRAW
            );

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); 
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint),
                m_indices.data(), GL_STATIC_DRAW
            );

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
            
            glBindVertexArray(0);
        }

        Mesh::~Mesh() {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_EBO);
        }
    }
}
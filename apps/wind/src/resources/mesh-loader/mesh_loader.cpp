#include "./../resources.h"

namespace app {
    class MeshLoader {    
    private:

        // tokenizer lines 
        std::vector<string> tokenize(string _line) {
            std::vector<string> tokens = {};
            std::stringstream buffer;

            uint pos = 0;
            while (pos < _line.size()) {
                if (_line[pos] == '#')
                    break;
                else if (_line[pos] == ' ') {
                    if (buffer.rdbuf()->in_avail() != 0)
                        tokens.push_back(buffer.str());
                    buffer.str("");
                } else if (_line[pos] == '/') {
                    tokens.push_back(buffer.str());
                    tokens.push_back("/");

                    buffer.str("");
                } else {
                    buffer << _line[pos];
                }

                ++pos;
            }

            if (buffer.rdbuf()->in_avail() != 0)
                tokens.push_back(buffer.str());

            return tokens;
        }

        //

    public:
        std::vector<vec3> vertices = {};
        std::vector<uint> indices = {};

        MeshLoader(string _path) {
            parse(_path);
        }
    private:
        std::vector<string> m_tokens;

        void parse(string _path) {
            // open file
            std::ifstream file(_path);
            if (!file.is_open())
                throw std::invalid_argument(
                    "Failed load obj mesh by path: " + _path
                );  

            string line;
            while (std::getline(file, line))
                lineParse(line);
        }

        void lineParse(string _line) {
            m_tokens = tokenize(_line);
            if (m_tokens.empty())
                return;

            string instruction = m_tokens[0];
            if (!isValidInstruction(instruction))
                return;

            if (instruction == "v" && m_tokens.size() >= 4)
                vertexParse();
            if (instruction == "f" && m_tokens.size() >= 4)
                faceParse();
        }

    private:
        void vertexParse() {
            float x = static_cast<float>(atof(m_tokens[1].c_str()));
            float y = static_cast<float>(atof(m_tokens[2].c_str()));
            float z = static_cast<float>(atof(m_tokens[3].c_str()));

            vertices.push_back({x, y, z});
        }

        void faceParse() {

            //===================================//

            std::vector<uint> inds{}; {
                ivec3 vnt = {};
                uint offset = 0;

                while (offset + 1 < m_tokens.size()) {
                    offset += vntParse(offset, vnt);
                    inds.push_back(vnt.x);
                }
            }
            
            //===================================//
            // triangulation convex polygon

            auto v = [](int i, std::vector<uint>& polygon){
                if (i < 0)
                    i = polygon.size() + i;
                i = i % polygon.size();
                return polygon[i];
            };

            for (int i = 0; inds.size() != 3; i += 2) {
                uint prev = v(i - 1, inds),
                     curr = v(i, inds),
                     next = v(i + 1, inds); 
                    
                indices.push_back(prev);
                indices.push_back(curr);
                indices.push_back(next);

                inds.erase(std::find(inds.begin(), inds.end(), curr));
            }

            indices.push_back(inds[0]);
            indices.push_back(inds[1]);
            indices.push_back(inds[2]);
        }

        // vertex/normal/textures
        uint vntParse(uint offset, ivec3& out) {
            int vertex = atoi(m_tokens[offset + 1].c_str()) - 1;
            if (m_tokens[offset + 2] != "/") {
                out = { vertex, 0, 0 };
                return 1;
            }
            
            int normal = atoi(m_tokens[offset + 3].c_str());
            if (m_tokens[offset + 4] != "/") {
                out = { vertex, normal, 0 };
                return 3;
            }

            int texture = atoi(m_tokens[offset + 5].c_str());
            out = { vertex, normal, texture };
            return 5;
        }

    private:

        bool isValidInstruction(string _instruction) {
            const static std::vector<string> INS = { "v", "f" };
            return (std::find(INS.begin(), INS.end(), _instruction) != INS.end());
        }
    };
   
    // .obj format load
    template <typename T>
    T* Resources::load(string _path) {
        MeshLoader loader(_path);

        return new Mesh(
            loader.vertices, loader.indices
        );
    }

    template Mesh* Resources::load<Mesh>(string);
}
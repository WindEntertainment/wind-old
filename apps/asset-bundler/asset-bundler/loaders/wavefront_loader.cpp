#include "wavefront_loader.h"
#include <algorithm>

namespace wind {
    namespace assets {
        ISerializable* WaveFrontObjLoader::load(const char* _path) {
            m_output_mesh = new Mesh();

            // open file
            std::ifstream file(_path);
            if (!file.is_open()) {
                log().error() << 
                    "Can't open file by path: [" << _path << "]";
                return nullptr;
            }

            // parsing
            string line;
            while (std::getline(file, line))
                lineParse(line);

            return m_output_mesh;
        }

        // tokenizer lines 
        vector<string> WaveFrontObjLoader::tokenize(string _line) const {
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

        bool WaveFrontObjLoader::isValidInstruction(string _instruction) const {
            const static std::vector<string> INS = { "v", "f" };
            return (std::find(INS.begin(), INS.end(), _instruction) != INS.end());
        }
        
        void WaveFrontObjLoader::lineParse(string _line) {
            auto tokens = tokenize(_line);
            if (tokens.empty())
                return;

            string instruction = tokens[0];
            if (!isValidInstruction(instruction))
                return;

            if (instruction == "v" && tokens.size() >= 4)
                vertexParse(tokens);
            if (instruction == "f" && tokens.size() >= 4)
                faceParse(tokens);
        }

        void WaveFrontObjLoader::vertexParse(vector<string>& _tokens) {
            float x = static_cast<float>(atof(_tokens[1].c_str()));
            float y = static_cast<float>(atof(_tokens[2].c_str()));
            float z = static_cast<float>(atof(_tokens[3].c_str()));

            m_output_mesh->vertices.push_back({x, y, z});
        }

        void WaveFrontObjLoader::faceParse(vector<string>& _tokens) {
            //===================================//

            std::vector<uint> inds{}; {
                glm::ivec3 vnt = {};
                uint offset = 0;

                while (offset + 1 < _tokens.size()) {
                    offset += vntParse(_tokens, offset, vnt);
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
                    
                m_output_mesh->indices.push_back(prev);
                m_output_mesh->indices.push_back(curr);
                m_output_mesh->indices.push_back(next);

                inds.erase(std::find(inds.begin(), inds.end(), curr));
            }

            m_output_mesh->indices.push_back(inds[0]);
            m_output_mesh->indices.push_back(inds[1]);
            m_output_mesh->indices.push_back(inds[2]);
        }

        // vertex/normal/textures
        uint WaveFrontObjLoader::vntParse(const vector<string>& _tokens, uint offset, glm::ivec3& out) const {
            int vertex = atoi(_tokens[offset + 1].c_str()) - 1;
            if (_tokens[offset + 2] != "/") {
                out = { vertex, 0, 0 };
                return 1;
            }
            
            int normal = atoi(_tokens[offset + 3].c_str());
            if (_tokens[offset + 4] != "/") {
                out = { vertex, normal, 0 };
                return 3;
            }

            int texture = atoi(_tokens[offset + 5].c_str());
            out = { vertex, normal, texture };
            return 5;
        }
    }
}
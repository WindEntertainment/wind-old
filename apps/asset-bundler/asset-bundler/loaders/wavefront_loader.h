#include "asset-bundler/objects/mesh.h"
#include "asset-bundler/loaders/iloader.h"

namespace wind {
    namespace assets {
        class WaveFrontObjLoader : public ILoader {
        private:
            Mesh* m_output_mesh;
        public:
            ISerializable* load(fs::path path) override;
        private:
            vector<string> tokenize(string _line) const;
            bool isValidInstruction(string _instruction) const;

            void lineParse(string _line);
            void vertexParse(vector<string>& tokens);
            void faceParse(vector<string>& tokens);

            uint vntParse(const vector<string>& _tokens, uint offset, glm::ivec3& out) const;
        };
    }
}
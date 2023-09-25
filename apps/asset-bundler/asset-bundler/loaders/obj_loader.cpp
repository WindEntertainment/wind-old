#include "obj_loader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace wind {
    namespace assets {
        ISerializable* ObjLoader::load(fs::path _path) {
            Assimp::Importer importer; // make a static?
            Mesh* out = nullptr;

            try {
                // load
                const struct aiScene * scene = importer.ReadFile(
                    _path.string().c_str(),
                    aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
                );

                // checks
                if (scene == nullptr)
                    throw std::invalid_argument(importer.GetErrorString());
                if (scene->mNumMeshes < 1)
                    throw std::invalid_argument("The file must have a mesh!");

                auto mesh = scene->mMeshes[0];
                for (uint i = 0; i < mesh->mNumFaces; ++i)
                    if (mesh->mFaces[i].mNumIndices != 3)
                        throw std::invalid_argument(
                            "Invalid format (face should be only with 3 vertex)"
                        );
                // 

                // copy data
                out = new Mesh();

                out->vertices.resize(mesh->mNumVertices);
                for (uint i = 0; i < mesh->mNumVertices; ++i)
                    out->vertices[i] = {
                        mesh->mVertices[i].x,
                        mesh->mVertices[i].y,
                        mesh->mVertices[i].z,
                    };

                out->indices.resize(mesh->mNumFaces * 3);
                for (uint i = 0; i < mesh->mNumFaces; ++i)
                    for (uint j = 0; j < 3; ++j)
                        out->indices[i * 3 + j] = mesh->mFaces[i].mIndices[j];


                out->uv.resize(mesh->mNumVertices);
                if (mesh->mTextureCoords[0]) {
                    for (uint i = 0; i < mesh->mNumVertices; ++i)
                        out->uv[i] = {
                            mesh->mTextureCoords[0][i].x,
                            mesh->mTextureCoords[0][i].y
                        };
                }
            } catch (std::exception& ex) {
                log().error() << "WaveFrontLoader: " << ex.what() << " by path: [" << _path << "]"; 
            }

            importer.FreeScene();
            return out;
        }
    }
}
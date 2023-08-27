#include "resources.h"

namespace app {
    template <typename T>
    T* Resources::load(string _path) {
        logger()->info() << "Loading shader by path:" << _path;

        //=======================================//
        //           PATH FORMATTING             //

        string vtx_path = _path + "_vtx.glsl",
               fgt_path = _path + "_fgt.glsl";

        //=======================================//
        //         OPEN AND READ FILE            //

        auto readFile = [](string _path) {
            // OPEN FILE  
            std::ifstream file(_path);
            if (!file.is_open())
                throw std::invalid_argument(
                    "Failed load shader by path: " + _path
                );  

            // READ FILE              
            string text = "", line;
            while (file.good()) {
                std::getline(file, line);
                text += line + "\n";
            }

            //
            file.close();
            return text;
        };

        //=======================================//
        //             CREATE SHADER             //

        auto vtx_shader = readFile(vtx_path);
        auto fgt_shader = readFile(fgt_path);

        return new Shader(
            vtx_shader.c_str(),
            fgt_shader.c_str()
        );
    }

    template Shader* Resources::load<Shader>(string);
}
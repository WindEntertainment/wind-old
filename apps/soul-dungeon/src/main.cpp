
/*
    base.json:
        {
            "field1": "Hello, "
        }
    other.json:
        {
            "field2": "World"
        }
    result.json:
        {
            "field1": "Hello, ",
            "field2": "World"
        }
*/

#include <iostream>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

const char* json1 = 
    "{\n"
    "\"field1\": \"Hello \"\n"
    "}\n";

const char* json2 = 
    "{\n"
    "\"field2\": \"World!\"\n"
    "}\n";

using namespace rapidjson;

Document doc1;
Document doc2;

int main() {
    std::cout << json1;
    std::cout << json2;

    doc1.Parse(json1);
    doc2.Parse(json2);

    
}

/*#include <asset-bundler/asset_bundler.h>
#include <asset-bundler/loaders/obj_loader.h>
#include <asset-bundler/loaders/shader_loader.h>
#include <asset-bundler/loaders/image_loader.h>
#include <asset-bundler/loaders/text_loader.h>

void bundler() {
    using namespace wind;

    assets::Bundler bundler;
    bundler.regLoader(".*(.obj)", new assets::ObjLoader());
    bundler.regLoader(".*(.glsl)", new assets::ShaderLoader());
    bundler.regLoader(".*(.jpg)", new assets::ImageLoader());
    bundler.regLoader(".*(.prefab)", new assets::TextLoader());

    bundler.assembly("./asset/", "./assets.bundle");
}

#include "game.h"
#include "level_one.h"

int game() {
    auto game = new soul_dungeon::Game();
    auto code = game->play(new soul_dungeon::LevelOne());
    delete game;
    return code;
}

int main(int argc, char** argv) {
    bundler();
    return game();
}*/
#include <asset-bundler/asset_bundler.h>
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

#include <dom/document.h>

int main(int argc, char** argv) {

    using namespace dom;
    
    Document* doc = new Document(); // FromXML("path"); FromJSON("path");
    
    if (auto components = doc->root()->getObject("components")) {
        if (components->getType() != TypeObject::CONTAINER)
            return EXIT_FAILURE;
        
        auto container = (Container*)components;
        for (auto obj : *container) {
            
        }
    }

    return EXIT_SUCCESS;

    /*bundler();
    return game();*/
}
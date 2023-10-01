#include <asset-bundler/asset_bundler.h>
#include <asset-bundler/loaders/obj_loader.h>
#include <asset-bundler/loaders/shader_loader.h>
#include <asset-bundler/loaders/image_loader.h>

void bundler() {
    using namespace wind;

    assets::Bundler bundler;
    bundler.regLoader(".*(.obj)", new assets::ObjLoader());
    bundler.regLoader(".*(.glsl)", new assets::ShaderLoader());
    bundler.regLoader(".*(.jpg)", new assets::ImageLoader());

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

#include <resources/resource_manager.h>

int main(int argc, char** argv) {

    bundler();
    auto bundle = new assets::Bundle("./assets.bundle");
    wind::resources::addBundle(bundle);
    auto mesh = wind::resources::get<assets::Mesh>("./asset/monkey.obj");
    log().debug() << (mesh == nullptr);

    return 0;
    bundler();
    return game();
}
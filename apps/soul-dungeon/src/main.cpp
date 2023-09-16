#include "asset-bundler/asset_bundler.h"
#include "asset-bundler/loaders/wavefront_loader.h"
#include "asset-bundler/loaders/shader_loader.h"

#include "asset-bundler/bundle.h"

int main(int argc, char** argv) {
    wind::assets::Bundler bundler;
    bundler.regLoader(".*(.obj)", new wind::assets::WaveFrontObjLoader());
    bundler.regLoader(".*(.glsl)", new wind::assets::ShaderLoader());
    bundler.assembly("./asset/", "assets.bundle");

    wind::assets::Bundle bundle;
    bundle.load("assets.bundle");

    auto monkey = bundle.getResource<wind::assets::Mesh>("./asset/monkey.obj");
    if (monkey) {
        wind::log().info() << monkey->id;
        wind::log().info() << monkey->vertices.size();
        wind::log().info() << monkey->indices.size();
    }

    auto shader = bundle.getResource<wind::assets::Shader>("./asset/shader_default.glsl");
    if (shader) {
        wind::log().info() << shader->vtx;
        wind::log().info() << shader->fgt;
    }
}
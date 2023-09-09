#include "asset-bundler/asset_bundler.h"
#include "asset-bundler/loaders/wavefront_loader.h"

int main(int argc, char** argv) {
    wind::assets::Bundler bundler;
    bundler.regLoader(".*(.obj)", new wind::assets::WaveFrontObjLoader());
    bundler.assembly("./asset/", "assets.bundle");
}
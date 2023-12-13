#include "earth.h"

namespace earth {

    void Application::build(const string&& path) {
        using namespace wind;

        assets::Bundler bundler;
        bundler.regLoader(".*(.obj)", new assets::ObjLoader());
        bundler.regLoader(".*(.glsl)", new assets::ShaderLoader());
        bundler.regLoader(".*(.jpg)", new assets::ImageLoader());
        bundler.regLoader(".*(.prefab)", new assets::TextLoader());

        bundler.assembly(std::move(path), "./assets.bundle");
    }
    
}
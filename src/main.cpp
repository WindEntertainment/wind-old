#include "application/Application.h"

int main(int argc, char** argv) {
    app::Resources::tryLoad<int>("./asset/shader.glsl");
    return app::Application::loop(argc, argv);
}
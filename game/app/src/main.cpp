#include "game/worlds/game-world.hpp"

int main(int argc, char** argv) {
#ifndef NDEBUG
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("----Debug configuration!----");
#endif

  AssetManager::loadBundle("res/Ultralight.bundle");
  AssetManager::loadBundle("res/Main.bundle");

  Window::init([](Window::Config* self) {
    self->title = "Game";
    self->fullScreen = false;
    self->size = {800, 600};
    self->vSync = true;
  });

  GameWorld gameWorld;
  gameWorld.load();

  while (Window::update()) {
    gameWorld.update();
    Window::show();
  }

  gameWorld.unload();
  Window::destroy();

  return EXIT_SUCCESS;
}

template <>
Texture* AssetManager::getAsset(const char* _key) {
  auto image = getAsset<Image>(_key);
  auto texture = new Texture(image->pixels, image->size);
  delete image;
  return texture;
}
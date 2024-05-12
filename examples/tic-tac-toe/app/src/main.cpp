#include "game/worlds.hpp"

int main(int argc, char** argv) {
#ifndef NDEBUG
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("----Debug configuration!----");
#endif

  AssetManager::loadBundle("res/Ultralight.bundle");
  AssetManager::loadBundle("res/Main.bundle");

  Window::init([](Window::Config* self) {
    self->title = "Tic Tac Toe";
    self->fullScreen = false;
    self->size = {600, 600};
    self->vSync = true;
  });

  InputSystem::createTriggersFromFile("main/configs/triggers.yml");

  World* world = loadGameWorld();

  while (Window::update()) {
    world->update();
    Window::show();
  }

  delete world;
  Window::destroy();

  return EXIT_SUCCESS;
}

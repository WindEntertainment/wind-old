#include "breeze.h"

#include <asset-bundler/bundle.h>
#include <resources/resource_manager.h>

namespace wind {
namespace breeze {
int Game::main(std::function<void(GameParameters* self)> _args) {
  //
  auto args = new GameParameters();
  _args(args);

  // library init
  system::Application::init([]() {
    return true;
  });

  // load resource bundle
  auto bundle = new assets::Bundle(std::move(args->bundle));
  if (!bundle->isOpen())
    return system::Application::terminate();
  resources::addBundle(bundle);

  // create window
  auto window = new system::Window(args->window);

  auto renderer = new renderer::Renderer();
  auto registry = new entt::registry();

  breeze::ComponentRegistry::init();

  auto scene = resources::get<breeze::Prefab>(args->scene.c_str());
  if (!scene) {
    log().error() << "Failed loading first scene: '" << args->scene << "'";
    return 1;
  }

  scene->instance(*registry); // instancnig scene
  delete scene;               // unload prefab

  return system::Application::loop([&]() {
    if (system::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
      system::Application::quit();

    renderer->clear();
    window->show();
  });
}
} // namespace breeze
} // namespace wind
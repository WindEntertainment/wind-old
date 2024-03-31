#include <renderer/renderer.hpp>

namespace wind {

class Node {};

class CompositeNode : public Node {
private:
  std::vector<Component*> m_components;

public:
  void addComponent(Component* _component);
};

class RenderTree : public Node {
private:
  std::vector<Renderable*> m_renderables;
};

class Component {
};

class Renderable : public Component {
};

} // namespace wind
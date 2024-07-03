
class JSEvents {
  struct HelloInput {
    std::string world;
  };
  struct HelloOutput {
    std::string world;
  };
  HelloOutput hello(const HelloInput& input) const;

};

class CppEvents {
  struct HelloInput {
    std::string world;
  };
  struct HelloOutput {
    int world;
  };
  HelloOutput hello(const HelloInput& input) const;

};

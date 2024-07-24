#pragma once
#include "Ultralight/Listener.h"

namespace wind {

namespace ul = ultralight;

class ViewLogger : public ul::ViewListener {
private:
  inline std::string toUTF8(const ul::String& str);
  inline const char* stringify(ul::MessageSource source);
  inline const char* stringify(ul::MessageLevel level);

public:
  void OnAddConsoleMessage(
    ul::View* caller,
    const ul::ConsoleMessage& log) override;
};

} // namespace wind

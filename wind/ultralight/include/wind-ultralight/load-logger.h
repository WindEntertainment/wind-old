#pragma once
#include "Ultralight/Listener.h"

namespace wind {

namespace ul = ultralight;

class LoadLogger : public ul::LoadListener {
public:
  std::function<void(ultralight::View*)> onDomReady;
  LoadLogger(std::function<void(ultralight::View*)> callback = nullptr) {
    this->onDomReady = callback;
  }

  void OnBeginLoading(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) override;
  void OnFinishLoading(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) override;
  void OnFailLoading(
    ul::View* caller, uint64_t frame_id, bool is_main_frame,
    const ul::String& url, const ul::String& description,
    const ul::String& error_domain, int error_code) override;
  void OnDOMReady(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) override;
};

} // namespace wind

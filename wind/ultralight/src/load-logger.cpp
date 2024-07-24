#include <spdlog/spdlog.h>
#include <wind-ultralight/ultralight.h>

#include <Ultralight/Ultralight.h>

namespace wind {

void LoadLogger::OnBeginLoading(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) {
  spdlog::info("[UL::Loader]: Loading started, url: {}", url.utf8().data());
};

void LoadLogger::OnFinishLoading(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) {
  spdlog::info("[UL::Loader]: Loading finished, url: {}", url.utf8().data());
};

void LoadLogger::OnFailLoading(
  ul::View* caller, uint64_t frame_id, bool is_main_frame,
  const ul::String& url, const ul::String& description,
  const ul::String& error_domain, int error_code) {
  spdlog::log(
    spdlog::level::err,
    "[UL::Loader]: Loading failed, error code: {}, description: {}, error domain: {}, url: {}",
    error_code,
    description.utf8().data(),
    error_domain.utf8().data(),
    url.utf8().data());
};

void LoadLogger::OnDOMReady(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) {
  this->onDomReady(caller);
  spdlog::info("[UL::Loader]: DOM ready, url: {}", url.utf8().data());
};

}; // namespace wind

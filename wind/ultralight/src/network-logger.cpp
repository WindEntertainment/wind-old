#include <spdlog/spdlog.h>
#include <wind-ultralight/ultralight.h>

#include <Ultralight/Ultralight.h>

namespace wind {

bool NetworkLogger::OnNetworkRequest(ultralight::View* caller, ul::NetworkRequest& request) {
  spdlog::info("[UL::Network]: {} request, url: {}", request.url().utf8().data(), request.httpMethod().utf8().data());
  return true;
};

}; // namespace wind

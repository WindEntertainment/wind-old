#pragma once
#include "Ultralight/Listener.h"

namespace wind {

namespace ul = ultralight;

class NetworkLogger : public ul::NetworkListener {
public:
  bool OnNetworkRequest(ultralight::View* caller, ul::NetworkRequest& request) override;
};

} // namespace wind

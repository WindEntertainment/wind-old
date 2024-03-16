#pragma once
#include "asset-pipeline/assets/asset.h"
#include <utils/utils.h>

namespace wind {

struct DefaultAsset : public Asset {
private:
  const uint* m_bytes;

public:
  DefaultAsset(const uint* bytes)
      : m_bytes(bytes) {
  }

  ~DefaultAsset() {
    delete[] m_bytes;
  }

  const uint* bytes() const {
    return m_bytes;
  }
};

} // namespace wind
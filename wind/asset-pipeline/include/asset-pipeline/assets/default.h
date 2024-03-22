#pragma once
#include "asset-pipeline/assets/asset.h"
#include <utils/utils.h>

namespace wind {

struct DefaultAsset : public Asset {
private:
  const unsigned char* m_bytes;

public:
  DefaultAsset(const unsigned char* bytes)
      : m_bytes(bytes) {
  }

  ~DefaultAsset() {
    delete[] m_bytes;
  }

  const unsigned char* bytes() const {
    return m_bytes;
  }
};

} // namespace wind
#pragma once
#include "logger.h"
#include <Ultralight/platform/FileSystem.h>
#include <asset-manager/asset-manager.hpp>

namespace wind {

class ULFileSystem : public ul::FileSystem {
public:
  bool FileExists(const ul::String& filePath) override {
    return AssetManager::exists(filePath.utf8().data());
  }

  ul::String GetFileMimeType(const ul::String& filePath) override {
    auto ext = fs::path(filePath.utf8().data()).extension().string();

    spdlog::debug("GetFileMimeType(): file: {} ext: {}", filePath.utf8().data(), ext);

    if (ext == ".html" || ext == ".htm")
      return "text/html";

    if (ext == ".css")
      return "text/css";

    if (ext == ".js")
      return "text/javascript";

    if (ext == ".svg")
      return "image/svg+xml";

    return "application/unknown";
  }

  ul::String GetFileCharset(const ul::String& filePath) override {
    return "utf-8";
  }

  ul::RefPtr<ul::Buffer> OpenFile(const ul::String& filePath) override {
    auto bytes = AssetManager::getAsset<unsigned char>(filePath.utf8().data());
    ul::RefPtr<ul::Buffer> buffer = ul::Buffer::Create(bytes,
                                                       strlen(reinterpret_cast<const char*>(bytes)),
                                                       nullptr,
                                                       nullptr);

    return buffer;
  }
};

} // namespace wind
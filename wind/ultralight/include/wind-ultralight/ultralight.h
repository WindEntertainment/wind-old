#pragma once
#include "renderer/texture.h"
#include <AppCore/Platform.h>
#include <Ultralight/Bitmap.h>
#include <Ultralight/Ultralight.h>
#include <map>

namespace UL = ultralight;

namespace wind {

class Ultralight {
    friend class UltralightViewManager;

public:
    static void init();

    static void initPlatform();

    static void createRenderer();

    static void updateLogic();

    static void renderOneFrame();
};

class UltralightViewManager {

public:
    static void loadView(const char* path);
    static void setTexture(UL::RefPtr<UL::View> view, Texture* texture);

    // private:
    static std::map<const char*, UL::RefPtr<UL::View>> views;
    static std::map<UL::RefPtr<UL::View>, Texture*> textures;
};

} // namespace wind

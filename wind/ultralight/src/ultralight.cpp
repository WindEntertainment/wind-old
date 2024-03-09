#include "AppCore/Platform.h"
#include "Ultralight/Bitmap.h"
#include "renderer/renderer.h"
#include "renderer/texture.h"
#include "utils/ext_string.h"
#include <algorithm>
#include <exception>
#include <glm/ext/scalar_uint_sized.hpp>
#include <wind-ultralight/ultralight.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace UL = ultralight;

namespace wind {

UL::RefPtr<UL::Renderer> ULRenderer;

void Ultralight::createRenderer() {
  ULRenderer = UL::Renderer::Create();
}

void Ultralight::initPlatform() {
  UL::Platform::instance().set_font_loader(UL::GetPlatformFontLoader());

  UL::Platform::instance().set_file_system(
      UL::GetPlatformFileSystem("./assets"));

  UL::Platform::instance().set_logger(UL::GetDefaultLogger("ultralight.log"));
}

void Ultralight::init() {
  UL::Config config;
  UL::Platform::instance().set_config(config);
}

// SDL_Texture* CopyBitmapToTexture(UL::RefPtr<UL::Bitmap> bitmap) {

// Uint32 sdlPixelFormat;
// if (bitmap->format() == UL::BitmapFormat::BGRA8_UNORM_SRGB) {
//     sdlPixelFormat = SDL_PIXELFORMAT_BGRA32;
// } else {

//     return nullptr;
// }

// SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(
//     0, bitmap->width(), bitmap->height(), 32, sdlPixelFormat);
// if (!surface) {

//     return nullptr;
// }

// Uint8* pixels = static_cast<Uint8*>(surface->pixels);
// const uint8_t* bitmapPixels = (uint8_t*)bitmap->LockPixels();
// const size_t rowBytes = bitmap->row_bytes();
// for (int y = 0; y < bitmap->height(); ++y) {
//     std::memcpy(pixels, bitmapPixels, rowBytes);
//     pixels += surface->pitch;
//     bitmapPixels += rowBytes;
// }
// bitmap->UnlockPixels();

// SDL_Texture* texture =
//     SDL_CreateTextureFromSurface(renderer->renderer, surface);

// SDL_FreeSurface(surface);

// return texture;
// }

void Ultralight::updateLogic() {
  ULRenderer->Update();
}

// SDL_Texture* texture;
UL::RefPtr<UL::View> globalView;
Texture* texture;

void Ultralight::renderOneFrame() {

  ULRenderer->Render();

  UL::BitmapSurface* surface = (UL::BitmapSurface*)(globalView->surface());

  if (!surface->dirty_bounds().IsEmpty()) {

    UL::RefPtr<UL::Bitmap> bitmap = surface->bitmap();

    const auto bitmapPixels = (unsigned char*)bitmap->LockPixels();

    if (texture)
      delete texture;
    texture = new Texture(bitmapPixels, bitmap->width(), bitmap->height());

    bitmap->UnlockPixels();

    surface->ClearDirtyBounds();
  }

  Renderer::drawTexture(texture, {10, 10}, {0, 0, 0}, {0, 0, 0}, {800, 600, 1});
}

std::map<const char*, UL::RefPtr<UL::View>> UltralightViewManager::views;
std::map<UL::RefPtr<UL::View>, Texture*> UltralightViewManager::textures;

void UltralightViewManager::setTexture(UL::RefPtr<UL::View> view,
                                       Texture* texture) {
  if (textures.contains(view)) {
    delete textures[view];
  }

  textures.insert(std::make_pair(view, texture));
}

void UltralightViewManager::loadView(const char* path) {
  UL::ViewConfig view_config;
  view_config.is_accelerated = false;

  UL::RefPtr<UL::View> view =
      ULRenderer->CreateView(800, 600, view_config, nullptr);

  string a = "file:///";
  a += path;

  // view->LoadHTML("<p>Hyi</p>");
  view->LoadURL(a.c_str());

  globalView = view;
  // views.insert(std::make_pair(path, view));
};
}; // namespace wind

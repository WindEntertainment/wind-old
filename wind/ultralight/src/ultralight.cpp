#include "AppCore/Platform.h"
#include "Ultralight/Bitmap.h"
#include "renderer/renderer.h"
#include "renderer/texture.h"
#include "utils/ext_string.h"
#include <algorithm>
#include <wind-ultralight/ultralight.h>

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

void Ultralight::renderOneFrame() {

  ULRenderer->Render();
  std::for_each(
      UltralightViewManager::views.begin(),
      UltralightViewManager::views.end(),
      [](auto pair) {
        UL::BitmapSurface* surface =
            (UL::BitmapSurface*)(pair.second->surface());

        if (!surface->dirty_bounds().IsEmpty()) {

          UL::RefPtr<UL::Bitmap> bitmap = surface->bitmap();

          const auto bitmapPixels =
              static_cast<unsigned char*>(bitmap->LockPixels());

          UltralightViewManager::setTexture(
              pair.second,
              new Texture(bitmapPixels, bitmap->width(), bitmap->height()));

          bitmap->UnlockPixels();

          surface->ClearDirtyBounds();
        }
      });

  std::for_each(UltralightViewManager::textures.begin(),
                UltralightViewManager::textures.end(),
                [](auto pair) {
                  Renderer::drawTexture(
                      pair.second, {1, 1}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1});
                });
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
      ULRenderer->CreateView(500, 500, view_config, nullptr);

  string a = "file:///";
  a += path;

  view->LoadHTML("<p>Hyi</p>");
  // view->LoadHTML(a.c_str());

  views.insert(std::make_pair(path, view));
};
}; // namespace wind

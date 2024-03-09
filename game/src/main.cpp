#include <renderer/particle.h>
#include <renderer/renderer.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

// namespace UL = ultralight;

// UL::RefPtr<UL::Renderer> ULRenderer;

// Window* window;

// Renderer* renderer;

// Resources* resources;

// void CreateRenderer() {
//     ULRenderer = UL::Renderer::Create();
// }

// UL::RefPtr<UL::View> view;

// void CreateView() {
//     UL::ViewConfig view_config;
//     view_config.is_accelerated = false;

//     view = ULRenderer->CreateView(500, 500, view_config, nullptr);

//     view->LoadURL("file:///page.html");
// }

// void InitPlatform() {
//     UL::Platform::instance().set_font_loader(UL::GetPlatformFontLoader());

//     UL::Platform::instance().set_file_system(UL::GetPlatformFileSystem("."));

//     UL::Platform::instance().set_logger(UL::GetDefaultLogger("ultralight.log"));
// }

// void Init() {
//     UL::Config config;
//     UL::Platform::instance().set_config(config);
// }

// SDL_Texture* CopyBitmapToTexture(UL::RefPtr<UL::Bitmap> bitmap) {

//     Uint32 sdlPixelFormat;
//     if (bitmap->format() == UL::BitmapFormat::BGRA8_UNORM_SRGB) {
//         sdlPixelFormat = SDL_PIXELFORMAT_BGRA32;
//     } else {

//         return nullptr;
//     }

//     SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(
//         0, bitmap->width(), bitmap->height(), 32, sdlPixelFormat);
//     if (!surface) {

//         return nullptr;
//     }

//     Uint8* pixels = static_cast<Uint8*>(surface->pixels);
//     const uint8_t* bitmapPixels = (uint8_t*)bitmap->LockPixels();
//     const size_t rowBytes = bitmap->row_bytes();
//     for (int y = 0; y < bitmap->height(); ++y) {
//         std::memcpy(pixels, bitmapPixels, rowBytes);
//         pixels += surface->pitch;
//         bitmapPixels += rowBytes;
//     }
//     bitmap->UnlockPixels();

//     SDL_Texture* texture =
//         SDL_CreateTextureFromSurface(renderer->renderer, surface);

//     SDL_FreeSurface(surface);

//     return texture;
// }

// void UpdateLogic() {
//     ULRenderer->Update();
// }

// SDL_Texture* texture;

// void RenderOneFrame() {
//     ULRenderer->Render();

//     UL::BitmapSurface* surface = (UL::BitmapSurface*)(view->surface());

//     if (!surface->dirty_bounds().IsEmpty()) {

//         if (texture) {
//             SDL_DestroyTexture(texture);
//         }

//         texture = CopyBitmapToTexture(surface->bitmap());

//         surface->ClearDirtyBounds();
//     }

//     renderer->drawTexture(texture, 0, 0);
// }

int main() {
  using namespace wind;
  Ultralight::init();
  Ultralight::initPlatform();
  Ultralight::createRenderer();
  UltralightViewManager::loadView("index.html");

  Window::init([](Window::Config* self) {
    self->title = "Game";
    self->fullScreen = false;
    self->size = {800, 600};
    self->vSync = false;
  });

  while (Window::update()) {
    if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
      Window::close();

    Renderer::clear({0.1f, 0.1f, 0.1f, 1});

    Ultralight::updateLogic();
    Ultralight::renderOneFrame();
    Renderer::drawRectangle({0, 0, 10, 10}, {0.4f, 0.4f, 0.4f, 1});
    Window::show();
  }

  return EXIT_SUCCESS;
}

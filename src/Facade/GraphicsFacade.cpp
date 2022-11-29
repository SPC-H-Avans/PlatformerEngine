#include "Facade/GraphicsFacade.hpp"
#include "Debug.hpp"
#include "Texture/TextureManager.hpp"

const int MAX_COLOR_VALUE = 255;


platformer_engine::GraphicsFacade::~GraphicsFacade() {
    Quit();
}

void platformer_engine::GraphicsFacade::Clear() {
    SDL_RenderClear(_renderer.get());
}

auto platformer_engine::GraphicsFacade::Init(int width, int height, const std::string &title,
                                             const spic::Color &color) -> bool {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    auto window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                                                     SDL_WINDOW_ALLOW_HIGHDPI);
    _window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
            SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                             window_flags), SDL_DestroyWindow);
    if (_window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    _renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>>(
            SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED),
            SDL_DestroyRenderer);
    if (_renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(_renderer.get(),
                           ConvertColorValueToSDLValue(color.GetRedValue()),
                           ConvertColorValueToSDLValue(color.GetGreenValue()),
                           ConvertColorValueToSDLValue(color.GetBlueValue()),
                           ConvertColorValueToSDLValue(color.GetAlphaValue()));
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_RenderSetLogicalSize(_renderer.get(), width, height);
    return true;
}

void platformer_engine::GraphicsFacade::Quit() {
    ClearTextures();
    SDL_DestroyRenderer(_renderer.get());
    SDL_DestroyWindow(_window.get());
    _renderer = nullptr;
    _window = nullptr;
    IMG_Quit();
    SDL_Quit();
}

void platformer_engine::GraphicsFacade::Render() {
    SDL_RenderPresent(_renderer.get());
}

auto platformer_engine::GraphicsFacade::ConvertColorValueToSDLValue(const double &colorValue) -> int {
    return NumberUtil::Clamp(static_cast<int>(colorValue * MAX_COLOR_VALUE), 0, MAX_COLOR_VALUE);
}

auto platformer_engine::GraphicsFacade::LoadTexture(const std::string &id, const std::string &fileName) -> bool {
    //load the textures file
    std::unique_ptr<SDL_Surface> surface(IMG_Load(fileName.c_str()));

    if (surface == nullptr) {
        spic::Debug::LogWarning("Failed to load texture: " + fileName + ", " + std::string(SDL_GetError()));
        return false;
    }

    std::unique_ptr<SDL_Texture, std::function<void(
            SDL_Texture *)>> texture = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>(
            SDL_CreateTextureFromSurface(_renderer.get(), surface.get()), SDL_DestroyTexture);

    if (texture == nullptr) {
        spic::Debug::LogWarning("Failed to create texture from surface: " + std::string(SDL_GetError()));
        return false;
    }

    _textureMap[id] = std::move(texture);
    return true;
}

void platformer_engine::GraphicsFacade::DrawTexture(const std::string &id, int x, int y, int width, int height,
                                                    const platformer_engine::SPIC_RendererFlip &flip, double scale) {
    SDL_Rect srcRect{0, 0, width, height};
    SDL_Rect destRect{x, y, (int)(width * scale), (int)(height * scale)};

    SDL_RenderCopyEx(_renderer.get(), _textureMap[id].get(), &srcRect, &destRect, 0, nullptr,
                     static_cast<const SDL_RendererFlip>(flip));
}

void platformer_engine::GraphicsFacade::DrawTile(const std::string &tileSetID, int tileSize, int x, int y, int row,
                                                 int frame, const SPIC_RendererFlip &flip, double scale) {
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};

//TODO CAMERA
//    Vector2D cam = Camera::GetInstance()->GetPosition();
//    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), tileSize, tileSize};
    SDL_Rect dstRect = {x, y, (int)(tileSize * scale), (int)(tileSize * scale)};
    SDL_RenderCopyEx(_renderer.get(), _textureMap[tileSetID].get(), &srcRect, &dstRect, 0, nullptr,
                     static_cast<const SDL_RendererFlip>(flip));
}

void
platformer_engine::GraphicsFacade::DrawFrame(const std::string &id, int x, int y, int width, int height, int row,
                                             int frame, const platformer_engine::SPIC_RendererFlip &flip, double scale) {
    SDL_Rect srcRect = {width * frame, height * (row - 1), width, height};
//TODO CAMERA
//    Vector2D cam = Camera::GetInstance()->GetPosition();
//    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), width, height};
    SDL_Rect dstRect = {x, y, (int)(width * scale), (int)(height * scale)};

    SDL_RenderCopyEx(_renderer.get(), _textureMap[id].get(), &srcRect, &dstRect, 0, nullptr,
                     static_cast<const SDL_RendererFlip>(flip));
}

void platformer_engine::GraphicsFacade::ClearTextures() {
    std::map<std::string, std::unique_ptr<SDL_Texture, std::function<void(
            SDL_Texture *)>>>::iterator it;
    for (it = _textureMap.begin(); it != _textureMap.end(); it++)
        SDL_DestroyTexture(it->second.get());

    _textureMap.clear();
}

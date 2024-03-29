#include <SDL2/SDL_ttf.h>
#include <tuple>

#include "Facade/GraphicsFacade.hpp"
#include "Debug.hpp"

const int MAX_COLOR_VALUE = 255;


platformer_engine::GraphicsFacade::~GraphicsFacade() {
    Quit();
}

void platformer_engine::GraphicsFacade::Clear() {
    SDL_RenderClear(_renderer.get());
}

auto platformer_engine::GraphicsFacade::Init(int width, int height, const std::string &title,
                                             const spic::Color &color, bool fullScreen) -> bool {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    auto window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_SHOWN |
                                                     SDL_WINDOW_ALLOW_HIGHDPI |
                                                     ((fullScreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
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
    const int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_RenderSetLogicalSize(_renderer.get(), width, height);
    TTF_Init();
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
    auto surface = std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>>(
            IMG_Load(fileName.c_str()),
            SDL_FreeSurface);
    if (surface == nullptr) {
        spic::Debug::LogWarning("Failed to load texture: " + fileName + ", " + std::string(SDL_GetError()));
        return false;
    }

    if(_renderer == nullptr) return false;

    auto texture = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>(
            SDL_CreateTextureFromSurface(_renderer.get(), surface.get()),
            SDL_DestroyTexture);
    if (texture == nullptr) {
        spic::Debug::LogWarning("Failed to create texture from surface: " + std::string(SDL_GetError()));
        return false;
    }

    _textureMap[id] = std::move(texture);

    return true;
}

auto platformer_engine::GraphicsFacade::CreateOrUpdateUIText(const std::string &textId, const std::string &filePath,
                                                             const std::string &text, const int fontSize,
                                                             const spic::Color &color) -> bool {
    // create the font
    auto font = std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>>(
            TTF_OpenFont(filePath.c_str(), fontSize),
            TTF_CloseFont);
    if (font == nullptr) {
        spic::Debug::LogWarning("Failed to font with path: " + filePath + ", " + std::string(TTF_GetError()));
        return false;
    }

    // create the surface
    const int maxColorValue = 255;
    const SDL_Color sdlColor = {
            static_cast<Uint8>(color.GetRedValue() * maxColorValue),
            static_cast<Uint8>(color.GetGreenValue() * maxColorValue),
            static_cast<Uint8>(color.GetBlueValue() * maxColorValue)};
    auto surface = std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>>(
            TTF_RenderText_Blended(font.get(), text.c_str(), sdlColor),
            SDL_FreeSurface);
    if (surface == nullptr) {
        spic::Debug::LogWarning("Failed to create surface from font: " + std::string(SDL_GetError()));
        return false;
    }

    if(_renderer == nullptr) return false;

    // create the texture
    std::unique_ptr<SDL_Texture, std::function<void(
            SDL_Texture *)>> texture = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>(
            SDL_CreateTextureFromSurface(_renderer.get(), surface.get()),
            SDL_DestroyTexture);
    if (texture == nullptr) {
        spic::Debug::LogWarning("Failed to create texture from surface: " + std::string(SDL_GetError()));
        return false;
    }

    // save
    _textureMap[textId] = std::move(texture);

    return true;
}

void platformer_engine::GraphicsFacade::DrawTexture(const std::string &id, int x, int y, int width, int height,
                                                    const platformer_engine::SPIC_RendererFlip &flip, double scale, double rotation,
                                                    int spriteSheetX, int spriteSheetY) {
    const SDL_Rect srcRect{spriteSheetX, spriteSheetY, width, height};
    const SDL_Rect destRect{x, y, static_cast<int>(width * scale), static_cast<int>(height * scale)};

    SDL_RenderCopyEx(_renderer.get(), _textureMap[id].get(), &srcRect, &destRect, rotation, nullptr,
                     static_cast<const SDL_RendererFlip>(flip));
}

void platformer_engine::GraphicsFacade::DrawUIText(const std::string &textId, const int x, const int y, const int width,
                                                   const int height) {
    const SDL_Rect rect {x, y, width, height};
    SDL_RenderCopy(_renderer.get(), _textureMap[textId].get(), nullptr, &rect);
}

void
platformer_engine::GraphicsFacade::DrawFrame(const std::string &id, int x, int y, int width, int height, int row,
                                             int frame, const platformer_engine::SPIC_RendererFlip &flip,
                                             double scale, double rotation) {
    const SDL_Rect srcRect = {width * frame, height * (row - 1), width, height};
//TODO CAMERA
//    Vector2D cam = Camera::GetInstance()->GetPosition();
//    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), width, height};
    const SDL_Rect dstRect = {x, y, (int) (width * scale), (int) (height * scale)};

    SDL_RenderCopyEx(_renderer.get(), _textureMap[id].get(), &srcRect, &dstRect, rotation, nullptr,
                     static_cast<const SDL_RendererFlip>(flip));
}

void platformer_engine::GraphicsFacade::ClearTextures() {
    std::map<std::string, std::unique_ptr<SDL_Texture, std::function<void(
            SDL_Texture *)>>>::iterator it;
    for (it = _textureMap.begin(); it != _textureMap.end(); it++)
        SDL_DestroyTexture(it->second.get());

    _textureMap.clear();
}

auto platformer_engine::GraphicsFacade::GetScreenSize() -> std::tuple<int, int> {
    int width = 0;
    int height = 0;
    SDL_GetRendererOutputSize(_renderer.get(), &width, &height);
    return std::make_tuple(width, height);
}

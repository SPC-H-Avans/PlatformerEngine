#include "GraphicsFacade/GraphicsFacade.hpp"

const int MAX_COLOR_VALUE = 255;

platformer_engine::GraphicsFacade::GraphicsFacade() {
    _window = nullptr;
    _renderer = nullptr;
}

platformer_engine::GraphicsFacade::~GraphicsFacade() {
    Quit();
}

void platformer_engine::GraphicsFacade::Clear() {
    SDL_RenderClear(_renderer.get());
}

bool platformer_engine::GraphicsFacade::Init(int width, int height, const std::string &title, const spic::Color &color) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    auto window_flags = (SDL_WindowFlags) (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
                           ConvertColorValueToSDLValue(color.getRedValue()),
                           ConvertColorValueToSDLValue(color.getGreenValue()),
                           ConvertColorValueToSDLValue(color.getBlueValue()),
                           ConvertColorValueToSDLValue(color.getAlphaValue()));
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(_renderer.get(), width, height);
    return true;

}

void platformer_engine::GraphicsFacade::Quit() {
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

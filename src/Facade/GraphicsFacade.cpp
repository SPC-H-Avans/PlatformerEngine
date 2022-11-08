//
// Created by Jaap Rodenburg on 07/11/2022.
//

#include "GraphicsFacade/GraphicsFacade.hpp"


PlatformerEngine::GraphicsFacade::GraphicsFacade() {
    window = nullptr;
    renderer = nullptr;
}

PlatformerEngine::GraphicsFacade::~GraphicsFacade() {
    Quit();
}

void PlatformerEngine::GraphicsFacade::Clear() {
    SDL_RenderClear(renderer.get());
}

bool PlatformerEngine::GraphicsFacade::Init(int width, int height, const std::string &title, const spic::Color &color) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    auto window_flags = (SDL_WindowFlags) (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
            SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                             window_flags), SDL_DestroyWindow);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>>(
            SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
            SDL_DestroyRenderer);
    if (renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(renderer.get(),
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
    SDL_RenderSetLogicalSize(renderer.get(), width, height);
    return true;

}

void PlatformerEngine::GraphicsFacade::Quit() {
    SDL_DestroyRenderer(renderer.get());
    SDL_DestroyWindow(window.get());
    renderer = nullptr;
    window = nullptr;
    IMG_Quit();
    SDL_Quit();
}

void PlatformerEngine::GraphicsFacade::Render() {
    SDL_RenderPresent(renderer.get());
}

int PlatformerEngine::GraphicsFacade::ConvertColorValueToSDLValue(const double &colorValue) {
    return NumberUtil::clamp(static_cast<int>(colorValue * 255), 0, 255);
}

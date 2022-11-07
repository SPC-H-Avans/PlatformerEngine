//
// Created by Jaap Rodenburg on 07/11/2022.
//

#include "GraphicsFacade/GraphicsFacade.h"


GraphicsFacade::GraphicsFacade() {
    window = nullptr;
    renderer = nullptr;
}

GraphicsFacade::~GraphicsFacade() {
    quit();
}

void GraphicsFacade::clear() {
    SDL_RenderClear(renderer);
}

void GraphicsFacade::init(int width, int height, const std::string& title, const Color& color) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        auto window_flags = (SDL_WindowFlags) (SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_ALWAYS_ON_TOP);
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
        if (window == nullptr) {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr) {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            } else {
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                }
            }
        }
    }
}

void GraphicsFacade::quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    IMG_Quit();
    SDL_Quit();
}

void GraphicsFacade::render() {
    SDL_RenderPresent(renderer);
}

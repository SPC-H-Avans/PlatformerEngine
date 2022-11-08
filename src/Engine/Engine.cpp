//
// Created by Jaap Rodenburg on 07/11/2022.
//
#include "Engine/Engine.hpp"

bool PlatformerEngine::Engine::Init(int width, int height, const std::string &title, const spic::Color &color) {
    if (window != nullptr) {
        return false;
    }
    window = std::make_unique<Window>(width, height, title, color);
    isRunning = true;
    while (isRunning) {
        auto &timer = Timer::Instance();
        timer.Update();
        //Add system here for input, delta time etc etc
        window->Render();
    }
    return true;
}

void PlatformerEngine::Engine::Render() {
    if (window == nullptr) {
        std::cout << "Can not render without initializing the engine first";
        return;
    }
    window->Render();
}

void PlatformerEngine::Engine::Quit() {
    window->Quit();
    isRunning = false;
}

//
// Created by Jaap Rodenburg on 07/11/2022.
//
#include "Render/Window.h"

PlatformerEngine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    graphicsFacade.Init(width, height, title, color);
}

void PlatformerEngine::Window::Render() {
    graphicsFacade.Clear();
    graphicsFacade.Render();
}

void PlatformerEngine::Window::Quit() {
    graphicsFacade.Quit();
}


//
// Created by Jaap Rodenburg on 07/11/2022.
//
#include "Render/Window.h"

PlatformerEngine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    graphicsFacade = GraphicsFacade();
    graphicsFacade.init(width, height, title, color);
}

void PlatformerEngine::Window::Render() {
    graphicsFacade.clear();
    graphicsFacade.render();
}

void PlatformerEngine::Window::Quit() {
    graphicsFacade.quit();
}


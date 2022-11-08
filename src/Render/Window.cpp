#include "Render/Window.hpp"

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


#include "Render/Window.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    graphicsFacade.Init(width, height, title, color);
}

void platformer_engine::Window::Render() {
    graphicsFacade.Clear();
    graphicsFacade.Render();
}

void platformer_engine::Window::Quit() {
    graphicsFacade.Quit();
}


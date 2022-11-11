#include "Render/Window.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    _graphicsFacade.Init(width, height, title, color);
}

void platformer_engine::Window::Render() {
    _graphicsFacade.Clear();
    _graphicsFacade.Render();
}

void platformer_engine::Window::Quit() {
    _graphicsFacade.Quit();
}

auto platformer_engine::Window::ListenForEvents() -> std::vector<EventsEnum> {
   return _inputFacade.ListenForInput();
}


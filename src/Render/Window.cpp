#include "Render/Window.hpp"
#include "Input/Input.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    _graphicsFacade.Init(width, height, title, color);
}

void platformer_engine::Window::Render() {
    if (Input::IsKeyPressed(Input::KEY_R)) SDL_Log("joe");
    if (Input::IsMouseButtonPressed(Input::MOUSE_RIGHT)) SDL_Log("nuts");
    auto foo = Input::GetMousePosition();
    SDL_Log("Mouse cursor is at %d, %d", std::get<0>(foo), std::get<1>(foo));
    _graphicsFacade.Clear();
    _graphicsFacade.Render();
}

void platformer_engine::Window::Quit() {
    _graphicsFacade.Quit();
}

auto platformer_engine::Window::ListenForEvents() -> std::vector<EventsEnum> {
   return _inputFacade.ListenForInput();
}


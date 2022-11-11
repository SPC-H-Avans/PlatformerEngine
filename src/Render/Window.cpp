#include "Render/Window.hpp"
#include "../../includes/spic-prj-api/Input.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    _graphicsFacade.Init(width, height, title, color);
}

void platformer_engine::Window::Render() {
//    auto foo = spic::Input::MousePosition();
//    SDL_Log("Mouse cursor is at %f, %f", foo.x, foo.y);
//    if (spic::Input::GetMouseButton(spic::Input::MouseButton::RIGHT)) SDL_Log("Right");
//    if (spic::Input::GetKey(spic::Input::KeyCode::A)) SDL_Log("a");
//    if (spic::Input::GetKey(spic::Input::KeyCode::B)) SDL_Log("b");
//    if (spic::Input::GetKey(spic::Input::KeyCode::KEYPAD_00)) SDL_Log("keypad");
    _graphicsFacade.Clear();
    _graphicsFacade.Render();
}

void platformer_engine::Window::Quit() {
    _graphicsFacade.Quit();
}

auto platformer_engine::Window::ListenForEvents() -> std::vector<EventsEnum> {
   return _inputFacade.ListenForInput();
}


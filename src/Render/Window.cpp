#include "Render/Window.hpp"
#include "../../includes/spic-prj-api/Input.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    _graphicsFacade.Init(width, height, title, color);
}

void platformer_engine::Window::Render() {
//    // mouse position
//    auto pos = spic::Input::MousePosition();
//    SDL_Log("Mouse cursor is at %f, %f", pos.x, pos.y);
//    // hold mouse
//    if (spic::Input::GetMouseButton(spic::Input::MouseButton::RIGHT)) SDL_Log("Right");
//    // hold valid key
//    if (spic::Input::GetKey(spic::Input::KeyCode::A)) SDL_Log("a");
//    if (spic::Input::GetKey(spic::Input::KeyCode::B)) SDL_Log("b");
//    // hold invalid key
//    if (spic::Input::GetKey(spic::Input::KeyCode::KEYPAD_00)) SDL_Log("keypad");
//    // hold any mouse/key
//    if (spic::Input::AnyKey()) SDL_Log("any held");
//    // press any mouse/key
//    if (spic::Input::AnyKeyDown()) SDL_Log("any press");
//    // mouse press/release
//    if (spic::Input::GetMouseButtonDown(spic::Input::MouseButton::LEFT)) SDL_Log("m1 down");
//    if (spic::Input::GetMouseButtonUp(spic::Input::MouseButton::LEFT)) SDL_Log("m1 up");
//    if (spic::Input::GetMouseButtonDown(spic::Input::MouseButton::RIGHT)) SDL_Log("m2 down");
//    if (spic::Input::GetMouseButtonUp(spic::Input::MouseButton::RIGHT)) SDL_Log("m2 up");
//    // key press/release
//    if (spic::Input::GetKeyDown(spic::Input::KeyCode::E)) SDL_Log("E press");
//    if (spic::Input::GetKeyUp(spic::Input::KeyCode::E)) SDL_Log("E release");
//    if (spic::Input::GetKeyDown(spic::Input::KeyCode::F)) SDL_Log("F press");
//    if (spic::Input::GetKeyUp(spic::Input::KeyCode::F)) SDL_Log("F release");

    _graphicsFacade.Clear();
    _graphicsFacade.Render();
}

void platformer_engine::Window::Quit() {
    _graphicsFacade.Quit();
}

auto platformer_engine::Window::ListenForEvents() -> std::vector<EventsEnum> {
   return _inputFacade.ListenForInput();
}


#include <tuple>

#include "Input.hpp"
#include "Debug.hpp"
#include "Facade/InputFacade.hpp"

auto spic::Input::MousePosition() -> spic::Point {
    std::tuple<int, int> position = platformer_engine::InputFacade::GetMousePosition();
    auto xPos = static_cast<double>(std::get<0>(position));
    auto yPos = static_cast<double>(std::get<1>(position));
    return Point {xPos, yPos};
}

auto spic::Input::AnyKey() -> bool {}

auto spic::Input::AnyKeyDown() -> bool {}

auto spic::Input::GetAxis() -> double {}

auto spic::Input::GetKey(spic::Input::KeyCode key) -> bool {
    auto facadeKey = platformer_engine::InputFacade::GetFacadeKeyCode(key);
    if (facadeKey == static_cast<int>(spic::Input::KeyCode::ERROR_UNDEFINED))
        spic::Debug::LogWarning("Use of undefined key");
    return platformer_engine::InputFacade::IsKeyPressed(facadeKey);
}

auto spic::Input::GetKeyDown(spic::Input::KeyCode key) -> bool {}

auto spic::Input::GetKeyUp(spic::Input::KeyCode key) -> bool {}

auto spic::Input::GetMouseButton(spic::Input::MouseButton which) -> bool {
    auto btn = platformer_engine::InputFacade::eMouseButton::MOUSE_LEFT;
    switch (which) {
        case MouseButton::LEFT: break;
        case MouseButton::MIDDLE:
            btn = platformer_engine::InputFacade::eMouseButton::MOUSE_MIDDLE; break;
        case MouseButton::RIGHT:
            btn = platformer_engine::InputFacade::eMouseButton::MOUSE_RIGHT; break;
    }
    return platformer_engine::InputFacade::IsMouseButtonPressed(btn);
}

auto spic::Input::GetMouseButtonDown(spic::Input::MouseButton which) -> bool {}

auto spic::Input::GetMouseButtonUp(spic::Input::MouseButton which) -> bool {}

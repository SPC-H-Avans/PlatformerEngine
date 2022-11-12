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

auto spic::Input::AnyKey() -> bool {
    return platformer_engine::InputFacade::IsAnyPressed();
}

auto spic::Input::AnyKeyDown() -> bool {}

auto spic::Input::GetAxis() -> double {
    // TODO: https://docs.unity3d.com/ScriptReference/Input.GetAxis.html
}

auto spic::Input::GetKey(spic::Input::KeyCode key) -> bool {
    auto facadeKey = platformer_engine::InputFacade::GetFacadeKeyCode(key); // TODO: instead of getting the facade's key here, set the key to the right one in the facade method
    if (facadeKey == static_cast<int>(spic::Input::KeyCode::ERROR_UNDEFINED))      // TODO: or maybe not? that makes the code less flexible
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

auto spic::Input::GetMouseButtonUp(spic::Input::MouseButton which) -> bool {
    // TODO: put this in separate method v
    auto btn = platformer_engine::InputFacade::eMouseButton::MOUSE_LEFT;
    switch (which) {
        case MouseButton::LEFT: break;
        case MouseButton::MIDDLE:
            btn = platformer_engine::InputFacade::eMouseButton::MOUSE_MIDDLE; break;
        case MouseButton::RIGHT:
            btn = platformer_engine::InputFacade::eMouseButton::MOUSE_RIGHT; break;
    }
    // TODO: put this in separate method ^
//    return platformer_engine::InputFacade::GetMouseUp(btn);
    return false;
}

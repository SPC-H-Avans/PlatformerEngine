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
    return platformer_engine::InputFacade::IsAnyHeld();
}

auto spic::Input::AnyKeyDown() -> bool {
    return platformer_engine::InputFacade::IsAnyPressed();
}

auto spic::Input::GetAxis() -> double {
    // Api bug: GetAxis has no parameter axisName (https://docs.unity3d.com/ScriptReference/Input.GetAxis.html)
    // TODO: implement once fixed
    spic::Debug::LogWarning("This method is currently not supported.");
}

auto spic::Input::GetKey(spic::Input::KeyCode key) -> bool {
    auto facadeKey = platformer_engine::InputFacade::GetFacadeKeyCode(key);
    if (facadeKey == static_cast<int>(spic::Input::KeyCode::ERROR_UNDEFINED)) // TODO: move to GetFacadeKeyCode
        spic::Debug::LogWarning("This key is not supported by the Facade");
    return platformer_engine::InputFacade::IsKeyHeld(facadeKey);
}

auto spic::Input::GetKeyDown(spic::Input::KeyCode key) -> bool {
    auto facadeKey = platformer_engine::InputFacade::GetFacadeKeyCode(key);
    return platformer_engine::InputFacade::GetKeyPress(facadeKey);
}

auto spic::Input::GetKeyUp(spic::Input::KeyCode key) -> bool {
    auto facadeKey = platformer_engine::InputFacade::GetFacadeKeyCode(key);
    return platformer_engine::InputFacade::GetKeyRelease(facadeKey);
}

auto spic::Input::GetMouseButton(spic::Input::MouseButton which) -> bool {
    auto btn = platformer_engine::InputFacade::GetFacadeMouseButtonCode(which);
    return platformer_engine::InputFacade::IsMouseButtonHeld(btn);
}

auto spic::Input::GetMouseButtonDown(spic::Input::MouseButton which) -> bool {
    auto btn = platformer_engine::InputFacade::GetFacadeMouseButtonCode(which);
    return platformer_engine::InputFacade::GetMousePress(btn);
}

auto spic::Input::GetMouseButtonUp(spic::Input::MouseButton which) -> bool {
    auto btn = platformer_engine::InputFacade::GetFacadeMouseButtonCode(which);
    return platformer_engine::InputFacade::GetMouseRelease(btn);
}

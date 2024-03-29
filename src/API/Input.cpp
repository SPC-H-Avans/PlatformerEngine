#include <tuple>

#include "Input.hpp"
#include "Debug.hpp"

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
    return platformer_engine::InputFacade::GetInstance().IsAnyPressed();
}

auto spic::Input::GetAxis() -> double {
    // Api bug: GetAxis has no parameter axisName (https://docs.unity3d.com/ScriptReference/Input.GetAxis.html)
    // TODO: implement once fixed
    spic::Debug::LogWarning("This method is currently not supported.");
    return 0;
}

auto spic::Input::GetKey(KeyCode key) -> bool {
    auto facadeKey = platformer_engine::InputFacade::GetFacadeKeyCode(key);
    return platformer_engine::InputFacade::IsKeyHeld(facadeKey);
}

auto spic::Input::GetKeyDown(KeyCode key) -> bool {
    auto facadeKey = platformer_engine::InputFacade::GetFacadeKeyCode(key);
    return platformer_engine::InputFacade::GetInstance().GetKeyPress(facadeKey);
}

auto spic::Input::GetKeyUp(KeyCode key) -> bool {
    auto facadeKey = platformer_engine::InputFacade::GetFacadeKeyCode(key);
    return platformer_engine::InputFacade::GetInstance().GetKeyRelease(facadeKey);
}

auto spic::Input::GetMouseButton(MouseButton which) -> bool {
    auto btn = platformer_engine::InputFacade::GetFacadeMouseButtonCode(which);
    return platformer_engine::InputFacade::IsMouseButtonHeld(btn);
}

auto spic::Input::GetMouseButtonDown(MouseButton which) -> bool {
    auto btn = platformer_engine::InputFacade::GetFacadeMouseButtonCode(which);
    return platformer_engine::InputFacade::GetInstance().GetMousePress(btn);
}

auto spic::Input::GetMouseButtonUp(MouseButton which) -> bool {
    auto btn = platformer_engine::InputFacade::GetFacadeMouseButtonCode(which);
    return platformer_engine::InputFacade::GetInstance().GetMouseRelease(btn);
}

auto spic::Input::ListenForInput() -> std::vector<EventsEnum> {
    return  platformer_engine::InputFacade::GetInstance().ListenForInput();
}

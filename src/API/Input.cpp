#include <tuple>

#include "Input.hpp"
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

auto spic::Input::GetKey(spic::Input::KeyCode key) -> bool {}

auto spic::Input::GetKeyDown(spic::Input::KeyCode key) -> bool {}

auto spic::Input::GetKeyUp(spic::Input::KeyCode key) -> bool {}

auto spic::Input::GetMouseButton(spic::Input::MouseButton which) -> bool {}

auto spic::Input::GetMouseButtonDown(spic::Input::MouseButton which) -> bool {}

auto spic::Input::GetMouseButtonUp(spic::Input::MouseButton which) -> bool {}

//auto platformer_engine::Input::ListenForInput() -> std::vector<EventsEnum> {
//    return _inputFacade.ListenForInput();
//}
//
//auto platformer_engine::Input::IsKeyPressed(eKey key) -> bool {
//    return InputFacade::IsKeyPressed(static_cast<InputFacade::eKey>(key));
//}
//
//auto platformer_engine::Input::IsMouseButtonPressed(eMouseButton button) -> bool {
//    return InputFacade::IsMouseButtonPressed(static_cast<InputFacade::eMouseButton>(button));
//}

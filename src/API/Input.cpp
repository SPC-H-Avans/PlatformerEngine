#include <tuple>

#include "Input.hpp"
#include "Facade/InputFacade.hpp"

bool spic::Input::GetKey(spic::Input::KeyCode key) {
    printf("joe");
    return true;
}

auto spic::Input::MousePosition() -> spic::Point {
    std::tuple<int, int> position = platformer_engine::InputFacade::GetMousePosition();
    auto xPos = static_cast<double>(std::get<0>(position));
    auto yPos = static_cast<double>(std::get<1>(position));
    return Point {xPos, yPos};
}

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
//
//auto platformer_engine::Input::GetMousePosition() -> std::tuple<int, int> {
//    return InputFacade::GetMousePosition();
//}

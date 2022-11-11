#include <tuple>

#include "Input/Input.hpp"

auto platformer_engine::Input::ListenForInput() -> std::vector<EventsEnum> {
    return _inputFacade.ListenForInput();
}

auto platformer_engine::Input::IsKeyPressed(eKey key) -> bool {
    return InputFacade::IsKeyPressed(static_cast<InputFacade::eKey>(key));
}

auto platformer_engine::Input::IsMouseButtonPressed(eMouseButton button) -> bool {
    return InputFacade::IsMouseButtonPressed(static_cast<InputFacade::eMouseButton>(button));
}

auto platformer_engine::Input::GetMousePosition() -> std::tuple<int, int> {
    return InputFacade::GetMousePosition();
}

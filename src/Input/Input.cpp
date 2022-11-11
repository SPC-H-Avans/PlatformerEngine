#include <tuple>

#include "Input/Input.h"

auto platformer_engine::Input::ListenForInput() -> std::vector<EventsEnum> {
    return _inputFacade.ListenForInput();
}

auto platformer_engine::Input::IsKeyPressed(InputFacade::eKey key) -> bool {
    return InputFacade::IsKeyPressed(key);
}

auto platformer_engine::Input::IsMouseButtonPressed(InputFacade::eMouseButton button) -> bool {
    return InputFacade::IsMouseButtonPressed(button);
}

auto platformer_engine::Input::GetMousePosition() -> std::tuple<int, int> {
    return InputFacade::GetMousePosition();
}

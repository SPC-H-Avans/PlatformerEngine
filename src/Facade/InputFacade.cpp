#include <vector>
#include <tuple>
#include "InputFacade.hpp"

platformer_engine::InputFacade::InputFacade() : _inputKeyStates(SDL_GetKeyboardState(nullptr)) {}

auto platformer_engine::InputFacade::ListenForInput() -> std::vector<EventsEnum> {
    SDL_Event event;
    std::vector<EventsEnum> events;

    //ADD LOGIC HERE TO ACTUALLY HANDLE EVENTS
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: events.push_back(EventsEnum::QUIT); break;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
        }
    }
    return events;
}

void platformer_engine::InputFacade::KeyUp() {
    _inputKeyStates = SDL_GetKeyboardState(nullptr);
}
void platformer_engine::InputFacade::KeyDown() {
    _inputKeyStates = SDL_GetKeyboardState(nullptr);
}

auto platformer_engine::InputFacade::IsKeyPressed(eKey key) -> bool {
    return SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey(key)] != 0U; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}

auto platformer_engine::InputFacade::IsMouseButtonPressed(eMouseButton button) -> bool {
    return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button)) != 0U;
}

auto platformer_engine::InputFacade::GetMousePosition() -> std::tuple<int, int> {
    int xPos = 0;
    int yPos = 0;
    SDL_GetMouseState(&xPos, &yPos);
    return std::make_tuple(xPos, yPos);
}
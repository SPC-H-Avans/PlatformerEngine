#include <vector>
#include <tuple>
#include <string>
#include "Facade/InputFacade.hpp"

platformer_engine::InputFacade::InputFacade() : _inputKeyStates(SDL_GetKeyboardState(nullptr)) {}

auto platformer_engine::InputFacade::ListenForInput() -> std::vector<EventsEnum> {
    SDL_Event event;
    std::vector<EventsEnum> events;

    auto foo = GetMousePosition();
//    SDL_Log("Mouse cursor is at %d, %d", std::get<0>(foo), std::get<1>(foo));
    if (GetKeyPressed(KEY_1)) {
        SDL_Log("1 is pressed");
    }

    //ADD LOGIC HERE TO ACTUALLY HANDLE EVENTS
    while (SDL_PollEvent(&event)){
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


auto platformer_engine::InputFacade::GetKeyPressed(eKey key) -> bool {
    return _inputKeyStates[SDL_GetScancodeFromKey(key)];
}

auto platformer_engine::InputFacade::GetMousePosition() -> std::tuple<int, int> {
    int xPos = 0;
    int yPos = 0;
    SDL_GetMouseState(&xPos, &yPos);
    return std::make_tuple(xPos, yPos);
}
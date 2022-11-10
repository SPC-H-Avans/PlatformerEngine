#include <vector>
#include "Facade/InputFacade.hpp"

platformer_engine::InputFacade::InputFacade() : _inputKeyStates(SDL_GetKeyboardState(nullptr)) {}

auto platformer_engine::InputFacade::ListenForInput() -> std::vector<EventsEnum> {
    SDL_Event event;
    std::vector<EventsEnum> events;

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

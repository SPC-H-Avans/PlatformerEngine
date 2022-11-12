#include <vector>
#include <tuple>

#include "InputFacade.hpp"
#include "Input.hpp"

platformer_engine::InputFacade::InputFacade() : _inputKeyStates(SDL_GetKeyboardState(nullptr)) {
}

auto platformer_engine::InputFacade::ListenForInput() -> std::vector<EventsEnum> {
    SDL_Event event;
    std::vector<EventsEnum> events;

    ClearKeys();

    //ADD LOGIC HERE TO ACTUALLY HANDLE EVENTS
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: events.push_back(EventsEnum::QUIT); break;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
            case SDL_MOUSEBUTTONDOWN:
                MouseDown(static_cast<eMouseButton>(event.button.button));
                break;
            case SDL_MOUSEBUTTONUP:
                MouseUp(static_cast<eMouseButton>(event.button.button));
                break;
        }
    }
    return events;
}

void platformer_engine::InputFacade::ClearKeys() {
    _mouseButtonsDown.clear();
    _mouseButtonsUp.clear();
}

void platformer_engine::InputFacade::KeyDown() {
//    SDL_Log("up");
    // TODO: Add logic here
    _inputKeyStates = SDL_GetKeyboardState(nullptr);
}
void platformer_engine::InputFacade::KeyUp() {
//    SDL_Log("down");
    // TODO: Add logic here
    _inputKeyStates = SDL_GetKeyboardState(nullptr);
}

void platformer_engine::InputFacade::MouseDown(eMouseButton button) {
    SDL_Log("down");
}
void platformer_engine::InputFacade::MouseUp(eMouseButton button) {
    SDL_Log(std::to_string(button).c_str());
    _mouseButtonsUp.push_back(button);
}

auto platformer_engine::InputFacade::IsAnyPressed() -> bool {
    // first check mouse buttons
    if (IsMouseButtonPressed(eMouseButton::MOUSE_LEFT) || IsMouseButtonPressed(eMouseButton::MOUSE_MIDDLE) ||
        IsMouseButtonPressed(eMouseButton::MOUSE_RIGHT)) {
        return true;
    }
    // then check keyboard
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        if (IsKeyPressed(i)) {
            return true;
        }
    }
    return false;
}

auto platformer_engine::InputFacade::IsKeyPressed(int key) -> bool {
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

auto platformer_engine::InputFacade::GetMouseUp(eMouseButton button) -> bool {
    std::vector<eMouseButton>::iterator it; // TODO: find which NOLINT to use
    for (it = _mouseButtonsUp.begin(); it != _mouseButtonsUp.end(); it++) {
        if (*it == button) {
            return true;
        }
    }
    return false;
}

auto platformer_engine::InputFacade::GetFacadeKeyCode(spic::Input::KeyCode key) -> int {
    switch (key) {
        case spic::Input::KeyCode::A: return KEY_A;
        case spic::Input::KeyCode::B: return KEY_B;
        case spic::Input::KeyCode::C: return KEY_C;
        case spic::Input::KeyCode::D: return KEY_D;
        case spic::Input::KeyCode::E: return KEY_E;
        case spic::Input::KeyCode::F: return KEY_F;
        case spic::Input::KeyCode::G: return KEY_G;
        case spic::Input::KeyCode::H: return KEY_H;
        case spic::Input::KeyCode::I: return KEY_I;
        case spic::Input::KeyCode::J: return KEY_J;
        case spic::Input::KeyCode::K: return KEY_K;
        case spic::Input::KeyCode::L: return KEY_L;
        case spic::Input::KeyCode::M: return KEY_M;
        case spic::Input::KeyCode::N: return KEY_N;
        case spic::Input::KeyCode::O: return KEY_O;
        case spic::Input::KeyCode::P: return KEY_P;
        case spic::Input::KeyCode::Q: return KEY_Q;
        case spic::Input::KeyCode::R: return KEY_R;
        case spic::Input::KeyCode::S: return KEY_S;
        case spic::Input::KeyCode::T: return KEY_T;
        case spic::Input::KeyCode::U: return KEY_U;
        case spic::Input::KeyCode::V: return KEY_V;
        case spic::Input::KeyCode::W: return KEY_W;
        case spic::Input::KeyCode::X: return KEY_X;
        case spic::Input::KeyCode::Y: return KEY_Y;
        case spic::Input::KeyCode::Z: return KEY_Z;
        case spic::Input::KeyCode::NUMBER_1_AND_EXCLAMATION: return KEY_1;
        case spic::Input::KeyCode::NUMBER_2_AND_AT: return KEY_2;
        case spic::Input::KeyCode::NUMBER_3_AND_HASHMARK: return KEY_3;
        case spic::Input::KeyCode::NUMBER_4_AND_DOLLAR: return KEY_4;
        case spic::Input::KeyCode::NUMBER_5_AND_PERCENTAGE: return KEY_5;
        case spic::Input::KeyCode::NUMBER_6_AND_CARET: return KEY_6;
        case spic::Input::KeyCode::NUMBER_7_AND_AMPERSAND: return KEY_7;
        case spic::Input::KeyCode::NUMBER_8_AND_ASTERISK: return KEY_8;
        case spic::Input::KeyCode::NUMBER_9_AND_OPENING_PARENTHESIS: return KEY_9;
        case spic::Input::KeyCode::NUMBER_0_AND_CLOSING_PARENTHESIS: return KEY_0;
        case spic::Input::KeyCode::F1: return KEY_F1;
        case spic::Input::KeyCode::F2: return KEY_F2;
        case spic::Input::KeyCode::F3: return KEY_F3;
        case spic::Input::KeyCode::F4: return KEY_F4;
        case spic::Input::KeyCode::F5: return KEY_F5;
        case spic::Input::KeyCode::F6: return KEY_F6;
        case spic::Input::KeyCode::F7: return KEY_F7;
        case spic::Input::KeyCode::F8: return KEY_F8;
        case spic::Input::KeyCode::F9: return KEY_F9;
        case spic::Input::KeyCode::F10: return KEY_F10;
        case spic::Input::KeyCode::F11: return KEY_F11;
        case spic::Input::KeyCode::F12: return KEY_F12;
        case spic::Input::KeyCode::UP_ARROW: return KEY_UP;
        case spic::Input::KeyCode::DOWN_ARROW: return KEY_DOWN;
        case spic::Input::KeyCode::LEFT_ARROW: return KEY_LEFT;
        case spic::Input::KeyCode::RIGHT_ARROW: return KEY_RIGHT;
        case spic::Input::KeyCode::SPACE: return KEY_SPACE;
        case spic::Input::KeyCode::ESCAPE: return KEY_ESCAPE;
        case spic::Input::KeyCode::RETURN: return KEY_RETURN;
        case spic::Input::KeyCode::BACKSPACE: return KEY_BACKSPACE;
        case spic::Input::KeyCode::TAB: return KEY_TAB;
        case spic::Input::KeyCode::LEFT_SHIFT: return KEY_LSHIFT;
        case spic::Input::KeyCode::RIGHT_SHIFT: return KEY_RSHIFT;
        case spic::Input::KeyCode::LEFT_CONTROL: return KEY_LCTRL;
        case spic::Input::KeyCode::RIGHT_CONTROL: return KEY_RCTRL;
        case spic::Input::KeyCode::LEFT_ALT: return KEY_LALT;
        case spic::Input::KeyCode::RIGHT_ALT: return KEY_RALT;
        case spic::Input::KeyCode::LEFT_GUI: return KEY_LGUI;
        case spic::Input::KeyCode::RIGHT_GUI: return KEY_RGUI;
        default: return static_cast<int>(spic::Input::KeyCode::ERROR_UNDEFINED);
    }
}

std::vector<platformer_engine::InputFacade::eMouseButton> platformer_engine::InputFacade::_mouseButtonsUp;
#include <vector>
#include <tuple>

#include "Facade/InputFacade.hpp"
#include "Debug.hpp"

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
            case SDL_KEYDOWN:
                KeyDown(static_cast<eKey>(event.key.keysym.sym));
                break; // For some reason, this continuously fires when a key is held down after half a second
            case SDL_KEYUP:
                KeyUp(static_cast<eKey>(event.key.keysym.sym));
            break;
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
    _mouseButtonsPressed.clear();
    _mouseButtonsReleased.clear();
    for (auto& [k, val] : _keysPressed) {
        val = false;
    }
    _keysReleased.clear();
}

void platformer_engine::InputFacade::KeyDown(eKey key) {
    // add key to keys down if it's not already there
    if (_keysPressed.count(key) > 0) {
        _keysPressed[key] = false;
    } else {
        _keysPressed.insert({key, true});
    }
    _inputKeyStates = SDL_GetKeyboardState(nullptr);
}
void platformer_engine::InputFacade::KeyUp(eKey key) {
    _keysReleased.push_back(key);
    // remove key from keys down if it's there
    if (_keysPressed.count(key) > 0) {
        _keysPressed.erase(key);
    }
    _inputKeyStates = SDL_GetKeyboardState(nullptr);
}

void platformer_engine::InputFacade::MouseDown(eMouseButton button) {
    _mouseButtonsPressed.push_back(button);
}
void platformer_engine::InputFacade::MouseUp(eMouseButton button) {
    _mouseButtonsReleased.push_back(button);
}

auto platformer_engine::InputFacade::IsAnyHeld() -> bool {
    // first check mouse buttons
    if (IsMouseButtonHeld(eMouseButton::MOUSE_LEFT) || IsMouseButtonHeld(eMouseButton::MOUSE_MIDDLE) ||
            IsMouseButtonHeld(eMouseButton::MOUSE_RIGHT)) {
        return true;
    }
    // then check keyboard
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) { // checks all keys on standard qwerty keyboard, but not all keys
        if (IsKeyHeld(static_cast<eKey>(i))) {
            return true;
        }
    }
    return false;
}

auto platformer_engine::InputFacade::IsAnyPressed() -> bool {
    // first check mouse buttons
    if (GetMousePress(eMouseButton::MOUSE_LEFT) || GetMousePress(eMouseButton::MOUSE_MIDDLE) ||
            GetMousePress(eMouseButton::MOUSE_RIGHT)) {
        return true;
    }
    // then check keyboard
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) { // checks all keys on standard qwerty keyboard, but not all keys
        if (GetKeyPress(static_cast<eKey>(i))) {
            return true;
        }
    }
    return false;
}

auto platformer_engine::InputFacade::IsKeyHeld(eKey key) -> bool {
    return SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey(key)] != 0U; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}

auto platformer_engine::InputFacade::GetKeyPress(eKey key) -> bool {
    if (_keysPressed.count(key) > 0) {
        return _keysPressed[key];
    }
    return false;
}

auto platformer_engine::InputFacade::GetKeyRelease(eKey key) -> bool {
    std::vector<eKey>::iterator itr;
    for (itr = _keysReleased.begin(); itr != _keysReleased.end(); itr++) {
        if (*itr == key) {
            return true;
        }
    }
    return false;
}

auto platformer_engine::InputFacade::IsMouseButtonHeld(eMouseButton button) -> bool {
    return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button)) != 0U;
}

auto platformer_engine::InputFacade::GetMousePosition() -> std::tuple<int, int> {
    int xPos = 0;
    int yPos = 0;
    SDL_GetMouseState(&xPos, &yPos);
    return std::make_tuple(xPos, yPos);
}

auto platformer_engine::InputFacade::GetMousePress(eMouseButton button) -> bool {
    std::vector<eMouseButton>::iterator itr;
    for (itr = _mouseButtonsPressed.begin(); itr != _mouseButtonsPressed.end(); itr++) {
        if (*itr == button) {
            return true;
        }
    }
    return false;
}

auto platformer_engine::InputFacade::GetMouseRelease(eMouseButton button) -> bool {
    std::vector<eMouseButton>::iterator itr;
    for (itr = _mouseButtonsReleased.begin(); itr != _mouseButtonsReleased.end(); itr++) {
        if (*itr == button) {
            return true;
        }
    }
    return false;
}

auto platformer_engine::InputFacade::GetFacadeKeyCode(KeyCode key) -> eKey {
    switch (key) {
        case KeyCode::A: return KEY_A;
        case KeyCode::B: return KEY_B;
        case KeyCode::C: return KEY_C;
        case KeyCode::D: return KEY_D;
        case KeyCode::E: return KEY_E;
        case KeyCode::F: return KEY_F;
        case KeyCode::G: return KEY_G;
        case KeyCode::H: return KEY_H;
        case KeyCode::I: return KEY_I;
        case KeyCode::J: return KEY_J;
        case KeyCode::K: return KEY_K;
        case KeyCode::L: return KEY_L;
        case KeyCode::M: return KEY_M;
        case KeyCode::N: return KEY_N;
        case KeyCode::O: return KEY_O;
        case KeyCode::P: return KEY_P;
        case KeyCode::Q: return KEY_Q;
        case KeyCode::R: return KEY_R;
        case KeyCode::S: return KEY_S;
        case KeyCode::T: return KEY_T;
        case KeyCode::U: return KEY_U;
        case KeyCode::V: return KEY_V;
        case KeyCode::W: return KEY_W;
        case KeyCode::X: return KEY_X;
        case KeyCode::Y: return KEY_Y;
        case KeyCode::Z: return KEY_Z;
        case KeyCode::NUMBER_1_AND_EXCLAMATION: return KEY_1;
        case KeyCode::NUMBER_2_AND_AT: return KEY_2;
        case KeyCode::NUMBER_3_AND_HASHMARK: return KEY_3;
        case KeyCode::NUMBER_4_AND_DOLLAR: return KEY_4;
        case KeyCode::NUMBER_5_AND_PERCENTAGE: return KEY_5;
        case KeyCode::NUMBER_6_AND_CARET: return KEY_6;
        case KeyCode::NUMBER_7_AND_AMPERSAND: return KEY_7;
        case KeyCode::NUMBER_8_AND_ASTERISK: return KEY_8;
        case KeyCode::NUMBER_9_AND_OPENING_PARENTHESIS: return KEY_9;
        case KeyCode::NUMBER_0_AND_CLOSING_PARENTHESIS: return KEY_0;
        case KeyCode::F1: return KEY_F1;
        case KeyCode::F2: return KEY_F2;
        case KeyCode::F3: return KEY_F3;
        case KeyCode::F4: return KEY_F4;
        case KeyCode::F5: return KEY_F5;
        case KeyCode::F6: return KEY_F6;
        case KeyCode::F7: return KEY_F7;
        case KeyCode::F8: return KEY_F8;
        case KeyCode::F9: return KEY_F9;
        case KeyCode::F10: return KEY_F10;
        case KeyCode::F11: return KEY_F11;
        case KeyCode::F12: return KEY_F12;
        case KeyCode::UP_ARROW: return KEY_UP;
        case KeyCode::DOWN_ARROW: return KEY_DOWN;
        case KeyCode::LEFT_ARROW: return KEY_LEFT;
        case KeyCode::RIGHT_ARROW: return KEY_RIGHT;
        case KeyCode::SPACE: return KEY_SPACE;
        case KeyCode::ESCAPE: return KEY_ESCAPE;
        case KeyCode::RETURN: return KEY_RETURN;
        case KeyCode::BACKSPACE: return KEY_BACKSPACE;
        case KeyCode::TAB: return KEY_TAB;
        case KeyCode::LEFT_SHIFT: return KEY_LSHIFT;
        case KeyCode::RIGHT_SHIFT: return KEY_RSHIFT;
        case KeyCode::LEFT_CONTROL: return KEY_LCTRL;
        case KeyCode::RIGHT_CONTROL: return KEY_RCTRL;
        case KeyCode::LEFT_ALT: return KEY_LALT;
        case KeyCode::RIGHT_ALT: return KEY_RALT;
        case KeyCode::LEFT_GUI: return KEY_LGUI;
        case KeyCode::RIGHT_GUI: return KEY_RGUI;
        default:
            spic::Debug::LogWarning("This key is not supported by the Facade");
            return static_cast<eKey>(KeyCode::ERROR_UNDEFINED);
    }
}

auto platformer_engine::InputFacade::GetFacadeMouseButtonCode(MouseButton button) -> eMouseButton {
    switch (button) {
        case MouseButton::LEFT:
            return MOUSE_LEFT; break;
        case MouseButton::MIDDLE:
            return MOUSE_MIDDLE; break;
        case MouseButton::RIGHT:
            return MOUSE_RIGHT; break;
        default: return MOUSE_LEFT;
    }
}

#ifndef PLATFORMER_GAME_INPUT_H
#define PLATFORMER_GAME_INPUT_H

#include <vector>
#include "../../../src/Facade/InputFacade.hpp"

namespace platformer_engine {
    class Input {
    public:
        enum eKey {
            KEY_UP = InputFacade::KEY_UP,
            KEY_DOWN = InputFacade::KEY_DOWN,
            KEY_LEFT = InputFacade::KEY_LEFT,
            KEY_RIGHT = InputFacade::KEY_RIGHT,
            KEY_SPACE = InputFacade::KEY_SPACE,
            KEY_ESCAPE = InputFacade::KEY_ESCAPE,
            KEY_RETURN = InputFacade::KEY_RETURN,
            KEY_BACKSPACE = InputFacade::KEY_BACKSPACE,
            KEY_TAB = InputFacade::KEY_TAB,
            KEY_LSHIFT = InputFacade::KEY_LSHIFT,
            KEY_RSHIFT = InputFacade::KEY_RSHIFT,
            KEY_LCTRL = InputFacade::KEY_LCTRL,
            KEY_RCTRL = InputFacade::KEY_RCTRL,
            KEY_LALT = InputFacade::KEY_LALT,
            KEY_RALT = InputFacade::KEY_RALT,
            KEY_LGUI = InputFacade::KEY_LGUI,
            KEY_RGUI = InputFacade::KEY_RGUI,
            KEY_A = InputFacade::KEY_A,
            KEY_B = InputFacade::KEY_B,
            KEY_C = InputFacade::KEY_C,
            KEY_D = InputFacade::KEY_D,
            KEY_E = InputFacade::KEY_E,
            KEY_F = InputFacade::KEY_F,
            KEY_G = InputFacade::KEY_G,
            KEY_H = InputFacade::KEY_H,
            KEY_I = InputFacade::KEY_I,
            KEY_J = InputFacade::KEY_J,
            KEY_K = InputFacade::KEY_K,
            KEY_L = InputFacade::KEY_L,
            KEY_M = InputFacade::KEY_M,
            KEY_N = InputFacade::KEY_N,
            KEY_O = InputFacade::KEY_O,
            KEY_P = InputFacade::KEY_P,
            KEY_Q = InputFacade::KEY_Q,
            KEY_R = InputFacade::KEY_R,
            KEY_S = InputFacade::KEY_S,
            KEY_T = InputFacade::KEY_T,
            KEY_U = InputFacade::KEY_U,
            KEY_V = InputFacade::KEY_V,
            KEY_W = InputFacade::KEY_W,
            KEY_X = InputFacade::KEY_X,
            KEY_Y = InputFacade::KEY_Y,
            KEY_Z = InputFacade::KEY_Z,
            KEY_0 = InputFacade::KEY_0,
            KEY_1 = InputFacade::KEY_1,
            KEY_2 = InputFacade::KEY_2,
            KEY_3 = InputFacade::KEY_3,
            KEY_4 = InputFacade::KEY_4,
            KEY_5 = InputFacade::KEY_5,
            KEY_6 = InputFacade::KEY_6,
            KEY_7 = InputFacade::KEY_7,
            KEY_8 = InputFacade::KEY_8,
            KEY_9 = InputFacade::KEY_9,
            KEY_F1 = InputFacade::KEY_F1,
            KEY_F2 = InputFacade::KEY_F2,
            KEY_F3 = InputFacade::KEY_F3,
            KEY_F4 = InputFacade::KEY_F4,
            KEY_F5 = InputFacade::KEY_F5,
            KEY_F6 = InputFacade::KEY_F6,
            KEY_F7 = InputFacade::KEY_F7,
            KEY_F8 = InputFacade::KEY_F8,
            KEY_F9 = InputFacade::KEY_F9,
            KEY_F10 = InputFacade::KEY_F10,
        };
        enum eMouseButton {
            MOUSE_LEFT = InputFacade::MOUSE_LEFT,
            MOUSE_MIDDLE = InputFacade::MOUSE_MIDDLE,
            MOUSE_RIGHT = InputFacade::MOUSE_RIGHT,
        };

        /**
         * @brief Listen of key input
         * @platformerengine
         */
        auto ListenForInput() -> std::vector<EventsEnum>;

        /**
         * @brief Check if a key is pressed
         * @param eKey The key to check
         * @platformerengine
         */
        static auto IsKeyPressed(eKey key) -> bool;

        /**
         * @brief Check if a mouse button is pressed
         * @param eMouseButton The mouse button to check
         * @platformerengine
         */
        static auto IsMouseButtonPressed(eMouseButton button) -> bool;

        /**
         * @brief Get the mouse position as a tuple of x and y
         * @platformerengine
         */
        static auto GetMousePosition() -> std::tuple<int, int>;
    private:
        InputFacade _inputFacade;
    };
} // namespace platformer_engine


#endif //PLATFORMER_GAME_INPUT_H

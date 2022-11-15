#ifndef PLATFORMER_ENGINE_INPUTFACADE_H
#define PLATFORMER_ENGINE_INPUTFACADE_H

#include <vector>
#include <map>

#include "SDL.h"
#include "Events/EventsEnum.h"
#include "Input.hpp"

namespace platformer_engine {
    class InputFacade {
    private:
        enum eKey {
            KEY_UP = SDLK_UP,
            KEY_DOWN = SDLK_DOWN,
            KEY_LEFT = SDLK_LEFT,
            KEY_RIGHT = SDLK_RIGHT,
            KEY_SPACE = SDLK_SPACE,
            KEY_ESCAPE = SDLK_ESCAPE,
            KEY_RETURN = SDLK_RETURN,
            KEY_BACKSPACE = SDLK_BACKSPACE,
            KEY_TAB = SDLK_TAB,
            KEY_LSHIFT = SDLK_LSHIFT,
            KEY_RSHIFT = SDLK_RSHIFT,
            KEY_LCTRL = SDLK_LCTRL,
            KEY_RCTRL = SDLK_RCTRL,
            KEY_LALT = SDLK_LALT,
            KEY_RALT = SDLK_RALT,
            KEY_LGUI = SDLK_LGUI,
            KEY_RGUI = SDLK_RGUI,
            KEY_A = SDLK_a,
            KEY_B = SDLK_b,
            KEY_C = SDLK_c,
            KEY_D = SDLK_d,
            KEY_E = SDLK_e,
            KEY_F = SDLK_f,
            KEY_G = SDLK_g,
            KEY_H = SDLK_h,
            KEY_I = SDLK_i,
            KEY_J = SDLK_j,
            KEY_K = SDLK_k,
            KEY_L = SDLK_l,
            KEY_M = SDLK_m,
            KEY_N = SDLK_n,
            KEY_O = SDLK_o,
            KEY_P = SDLK_p,
            KEY_Q = SDLK_q,
            KEY_R = SDLK_r,
            KEY_S = SDLK_s,
            KEY_T = SDLK_t,
            KEY_U = SDLK_u,
            KEY_V = SDLK_v,
            KEY_W = SDLK_w,
            KEY_X = SDLK_x,
            KEY_Y = SDLK_y,
            KEY_Z = SDLK_z,
            KEY_0 = SDLK_0,
            KEY_1 = SDLK_1,
            KEY_2 = SDLK_2,
            KEY_3 = SDLK_3,
            KEY_4 = SDLK_4,
            KEY_5 = SDLK_5,
            KEY_6 = SDLK_6,
            KEY_7 = SDLK_7,
            KEY_8 = SDLK_8,
            KEY_9 = SDLK_9,
            KEY_F1 = SDLK_F1,
            KEY_F2 = SDLK_F2,
            KEY_F3 = SDLK_F3,
            KEY_F4 = SDLK_F4,
            KEY_F5 = SDLK_F5,
            KEY_F6 = SDLK_F6,
            KEY_F7 = SDLK_F7,
            KEY_F8 = SDLK_F8,
            KEY_F9 = SDLK_F9,
            KEY_F10 = SDLK_F10,
            KEY_F11 = SDLK_F11,
            KEY_F12 = SDLK_F12,
        };
        enum eMouseButton {
            MOUSE_LEFT = SDL_BUTTON_LEFT,
            MOUSE_MIDDLE = SDL_BUTTON_MIDDLE,
            MOUSE_RIGHT = SDL_BUTTON_RIGHT,
        };
    public:
        static inline auto GetInstance() -> InputFacade & {
            static InputFacade instance;
            return instance;
        }

        InputFacade(const InputFacade&) = delete;
        auto operator=(const InputFacade&) -> InputFacade& = delete;
        InputFacade(InputFacade &&) = delete;
        void operator=(InputFacade &&) = delete;

        /**
         * @brief Listen of key input
         * @platformerengine
         */
        auto ListenForInput() -> std::vector<EventsEnum>;

        static auto IsAnyHeld() -> bool;

        auto IsAnyPressed() -> bool;

        /**
         * @brief Check if a key is pressed
         * @param eKey The key to check
         * @platformerengine
         */
        static auto IsKeyHeld(eKey key) -> bool;

        auto GetKeyPress(eKey key) -> bool;

        auto GetKeyRelease(eKey key) -> bool;

        /**
         * @brief Check if a mouse button is pressed
         * @param eMouseButton The mouse button to check
         * @platformerengine
         */
        static auto IsMouseButtonHeld(eMouseButton button) -> bool;

        /**
         * @brief Get the mouse position as a tuple of x and y
         * @platformerengine
         */
        static auto GetMousePosition() -> std::tuple<int, int>;

        auto GetMousePress(eMouseButton button) -> bool;

        auto GetMouseRelease(eMouseButton button) -> bool;

        static auto GetFacadeKeyCode(spic::Input::KeyCode key) -> eKey;

        static auto GetFacadeMouseButtonCode(spic::Input::MouseButton button) -> eMouseButton;

    private:
        InputFacade() = default; // TODO
        ~InputFacade() = default;

        void ClearKeys();
        void KeyDown(eKey key);
        void KeyUp(eKey key);
        void MouseDown(eMouseButton button);
        void MouseUp(eMouseButton button);
        const Uint8* _inputKeyStates;
        std::map<eKey, bool> _keysPressed; // because SDL_KEYDOWN can trigger multiple times, the second bool denotes if the key should trigger
        std::vector<eKey> _keysReleased;
        std::vector<eMouseButton> _mouseButtonsPressed;
        std::vector<eMouseButton> _mouseButtonsReleased;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_INPUTFACADE_H

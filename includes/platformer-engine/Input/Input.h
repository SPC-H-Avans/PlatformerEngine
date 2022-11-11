#ifndef PLATFORMER_GAME_INPUT_H
#define PLATFORMER_GAME_INPUT_H

#include <vector>
#include "../Facade/InputFacade.hpp"

namespace platformer_engine {
    class Input {
    public:
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
        static auto IsKeyPressed(InputFacade::eKey key) -> bool;

        /**
         * @brief Check if a mouse button is pressed
         * @param eMouseButton The mouse button to check
         * @platformerengine
         */
        static auto IsMouseButtonPressed(InputFacade::eMouseButton button) -> bool;

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

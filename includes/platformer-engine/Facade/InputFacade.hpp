#ifndef PLATFORMER_ENGINE_INPUTFACADE_H
#define PLATFORMER_ENGINE_INPUTFACADE_H

#include "SDL.h"
#include "Events/EventsEnum.h"

namespace platformer_engine{
    class InputFacade{
    public:
        InputFacade();

        /**
         * @brief Listen of key input
         */
        auto ListenForInput() -> std::vector<EventsEnum>;

    private:
        void KeyUp();
        void KeyDown();
        const Uint8* _inputKeyStates;
    };
}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_INPUTFACADE_H

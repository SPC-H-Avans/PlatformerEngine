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
        std::vector<EventsEnum> ListenForInput();

    private:
        void KeyUp();
        void KeyDown();
        const Uint8* _inputKeyStates;
    };
}

#endif //PLATFORMER_ENGINE_INPUTFACADE_H

#ifndef PLATFORMER_ENGINE_NOWINDOWEXCEPTION_H
#define PLATFORMER_ENGINE_NOWINDOWEXCEPTION_H

#include <stdexcept>

namespace spic {
    class NoWindowException : public std::logic_error
    {
    public:
        NoWindowException () : std::logic_error{"The window class has not been created yet! Please initialize the engine first"} {}
    };
}
#endif //PLATFORMER_ENGINE_NOWINDOWEXCEPTION_H

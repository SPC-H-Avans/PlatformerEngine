#ifndef PLATFORMER_ENGINE_SERVERALREADYACTIVEEXCEPTION_HPP
#define PLATFORMER_ENGINE_SERVERALREADYACTIVEEXCEPTION_HPP
#include <stdexcept>

namespace spic {
    class ServerAlreadyActiveException : public std::logic_error
    {
    public:
        ServerAlreadyActiveException () : std::logic_error{"There is already a server running! Please close it first."} {}
    };
}
#endif //PLATFORMER_ENGINE_SERVERALREADYACTIVEEXCEPTION_HPP

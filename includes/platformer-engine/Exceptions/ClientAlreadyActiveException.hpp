#ifndef PLATFORMER_ENGINE_CLIENTALREADYACTIVEEXCEPTION_HPP
#define PLATFORMER_ENGINE_CLIENTALREADYACTIVEEXCEPTION_HPP
#include <stdexcept>

namespace spic {
    class ClientAlreadyActiveException : public std::logic_error
    {
    public:
        ClientAlreadyActiveException () : std::logic_error{"There is already a client running! Please close it first."} {}
    };
}
#endif //PLATFORMER_ENGINE_CLIENTALREADYACTIVEEXCEPTION_HPP

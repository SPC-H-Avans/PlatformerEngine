#ifndef PLATFORMER_ENGINE_COULDNOTCONNECTTOSERVEREXCEPTION_HPP
#define PLATFORMER_ENGINE_COULDNOTCONNECTTOSERVEREXCEPTION_HPP
#include <stdexcept>

namespace spic {
    class CouldNotConnectToServerException : public std::logic_error
    {
    public:
        CouldNotConnectToServerException () : std::logic_error{"Unable to connect to client"} {}
    };
}

#endif //PLATFORMER_ENGINE_COULDNOTCONNECTTOSERVEREXCEPTION_HPP

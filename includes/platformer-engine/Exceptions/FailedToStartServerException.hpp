
#ifndef PLATFORMER_ENGINE_FAILEDTOSTARTSERVEREXCEPTION_HPP
#define PLATFORMER_ENGINE_FAILEDTOSTARTSERVEREXCEPTION_HPP
#include <stdexcept>

namespace spic {
    class FailedToStartServerException : public std::logic_error
    {
    public:
        FailedToStartServerException (int port) : std::logic_error{"Something went wrong while trying to start a server at port: " + std::to_string(port) + ". Is it already running??"} {}
    };
}
#endif //PLATFORMER_ENGINE_FAILEDTOSTARTSERVEREXCEPTION_HPP

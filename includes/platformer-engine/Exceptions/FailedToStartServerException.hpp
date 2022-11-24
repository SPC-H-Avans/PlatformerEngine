
#ifndef PLATFORMER_ENGINE_FAILEDTOSTARTSERVEREXCEPTION_HPP
#define PLATFORMER_ENGINE_FAILEDTOSTARTSERVEREXCEPTION_HPP
#include <stdexcept>

namespace spic {
    class FailedToStartServerException : public std::logic_error
    {
    public:
        FailedToStartServerException () : std::logic_error{"Something went wrong while trying to start a server. Is it already running??"} {}
    };
}
#endif //PLATFORMER_ENGINE_FAILEDTOSTARTSERVEREXCEPTION_HPP

#ifndef PLATFORMER_ENGINE_SERVERCOULDNOTBEINITIALIZED_HPP
#define PLATFORMER_ENGINE_SERVERCOULDNOTBEINITIALIZED_HPP

#include <stdexcept>

namespace spic {
    class ServerCouldNotBeInitialized : public std::logic_error
    {
    public:
        ServerCouldNotBeInitialized () : std::logic_error{"There is already a server running! Please close it first."} {}
    };
}
#endif //PLATFORMER_ENGINE_SERVERCOULDNOTBEINITIALIZED_HPP

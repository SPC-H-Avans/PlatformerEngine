#ifndef PLATFORMER_ENGINE_NETWORKINGCOULDNOTBEINITIALIZED_HPP
#define PLATFORMER_ENGINE_NETWORKINGCOULDNOTBEINITIALIZED_HPP

#include <stdexcept>

namespace spic {
    class NetworkingCouldNotBeInitialized : public std::logic_error
    {
    public:
        NetworkingCouldNotBeInitialized () : std::logic_error{"Failed to initialize the networking component"} {}
    };
}
#endif //PLATFORMER_ENGINE_NETWORKINGCOULDNOTBEINITIALIZED_HPP

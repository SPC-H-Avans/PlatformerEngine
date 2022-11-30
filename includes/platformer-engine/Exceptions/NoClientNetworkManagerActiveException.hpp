#ifndef PLATFORMER_ENGINE_NOCLIENTNETWORKMANAGERACTIVEEXCEPTION_HPP
#define PLATFORMER_ENGINE_NOCLIENTNETWORKMANAGERACTIVEEXCEPTION_HPP

#include <stdexcept>

namespace spic {
    class NoClientNetworkManagerActiveException : public std::logic_error
    {
    public:
        NoClientNetworkManagerActiveException () : std::logic_error{"There is no Client Network Manager active!"} {}
    };
}
#endif //PLATFORMER_ENGINE_NOCLIENTNETWORKMANAGERACTIVEEXCEPTION_HPP

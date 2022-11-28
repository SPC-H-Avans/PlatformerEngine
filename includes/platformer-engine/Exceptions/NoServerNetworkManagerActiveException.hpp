#ifndef PLATFORMER_ENGINE_NOSERVERNETWORKMANAGERACTIVEEXCEPTION_HPP
#define PLATFORMER_ENGINE_NOSERVERNETWORKMANAGERACTIVEEXCEPTION_HPP

#include <stdexcept>

namespace spic {
    class NoServerNetworkManagerActiveException : public std::logic_error
    {
    public:
        NoServerNetworkManagerActiveException () : std::logic_error{"There is no Server Network Manager active!"} {}
    };
}
#endif //PLATFORMER_ENGINE_NOSERVERNETWORKMANAGERACTIVEEXCEPTION_HPP

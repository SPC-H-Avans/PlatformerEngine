#ifndef PLATFORMER_ENGINE_TOOMANYSERVERSLOTSEXCEPTION_HPP
#define PLATFORMER_ENGINE_TOOMANYSERVERSLOTSEXCEPTION_HPP
#include <stdexcept>

namespace spic {
    class InvalidPlayerSlotsException : public std::logic_error
    {
    public:
        InvalidPlayerSlotsException (int chosenSlots, int minSlots, int maxSlots) : std::logic_error{"Invalid player slot amount chosen! Please use a slot range between " + std::to_string(minSlots) + "-" +  std::to_string(maxSlots) + ", you used: " + std::to_string(chosenSlots)} {}
    };
}
#endif //PLATFORMER_ENGINE_TOOMANYSERVERSLOTSEXCEPTION_HPP

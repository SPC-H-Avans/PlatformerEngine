#ifndef PLATFORMER_ENGINE_TOOMANYSERVERSLOTSEXCEPTION_HPP
#define PLATFORMER_ENGINE_TOOMANYSERVERSLOTSEXCEPTION_HPP
#include <stdexcept>

namespace spic {
    class InvalidPlayerSlotsException : public std::logic_error
    {
    public:
        InvalidPlayerSlotsException (int chosenSlots) : std::logic_error{"Invalid player slot amount chosen! Please use a slot range between 1-1000, you used: " + std::to_string(chosenSlots)} {}
    };
}
#endif //PLATFORMER_ENGINE_TOOMANYSERVERSLOTSEXCEPTION_HPP

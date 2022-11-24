#ifndef PLATFORMER_ENGINE_INVALIDPORTEXCEPTION_HPP
#define PLATFORMER_ENGINE_INVALIDPORTEXCEPTION_HPP
#include <stdexcept>

namespace spic {
    class InvalidPortException : public std::logic_error
    {
    public:
        InvalidPortException (int chosenPort) : std::logic_error{std::to_string(chosenPort) + " is not an allowed port! Please use a port between 1-65535"} {}
    };
}
#endif //PLATFORMER_ENGINE_INVALIDPORTEXCEPTION_HPP

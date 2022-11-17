#ifndef PLATFORMER_ENGINE_INVALIDSIZEEXCEPTION_H
#define PLATFORMER_ENGINE_INVALIDSIZEEXCEPTION_H

#include <stdexcept>

namespace spic {
    class InvalidSizeException : public std::logic_error
    {
    public:
        InvalidSizeException (const std::string& wrongSize, const std::string& sizeRule ) : std::logic_error{"Invalid size provided: " + wrongSize + ", " + sizeRule} {}
    };
}

#endif //PLATFORMER_ENGINE_INVALIDSIZEEXCEPTION_H

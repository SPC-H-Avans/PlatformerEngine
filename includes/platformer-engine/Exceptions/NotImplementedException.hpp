#ifndef PLATFORMER_ENGINE_NOTIMPLEMENTEDEXCEPTION_H
#define PLATFORMER_ENGINE_NOTIMPLEMENTEDEXCEPTION_H

#include <stdexcept>

namespace spic {
    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException () : std::logic_error{"Function not yet implemented."} {}
    };
}

#endif //PLATFORMER_ENGINE_NOTIMPLEMENTEDEXCEPTION_H

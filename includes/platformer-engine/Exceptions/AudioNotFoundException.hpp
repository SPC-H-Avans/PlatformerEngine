
#ifndef PLATFORMER_ENGINE_AUDIONOTFOUNDEXCEPTION_H
#define PLATFORMER_ENGINE_AUDIONOTFOUNDEXCEPTION_H

#include <stdexcept>

namespace spic {
    class AudioNotFoundException : public std::logic_error
    {
    public:
        AudioNotFoundException (const std::string& fileName) : std::logic_error{"The audio file could not be found!"} {}
    };
}
#endif //PLATFORMER_ENGINE_AUDIONOTFOUNDEXCEPTION_H

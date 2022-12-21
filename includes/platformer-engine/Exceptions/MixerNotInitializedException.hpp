
#ifndef PLATFORMER_ENGINE_MIXERNOTINITIALIZEDEXCEPTION_H
#define PLATFORMER_ENGINE_MIXERNOTINITIALIZEDEXCEPTION_H

#include <stdexcept>

namespace spic {
    class MixerNotInitializedException : public std::logic_error
    {
    public:
        MixerNotInitializedException (const std::string& mixerError) : std::logic_error{mixerError} {}
    };
}
#endif //PLATFORMER_ENGINE_MIXERNOTINITIALIZEDEXCEPTION_H

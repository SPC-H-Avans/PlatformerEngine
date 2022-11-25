#ifndef PLATFORMER_ENGINE_SCENENOTLOADEDEXCEPTION_HPP
#define PLATFORMER_ENGINE_SCENENOTLOADEDEXCEPTION_HPP

#include <stdexcept>

namespace spic {
    class SceneNotLoadedException : public std::logic_error {
    public:
        SceneNotLoadedException() : std::logic_error{
                "This scene is not loaded! Please load it first"} {}
    };
}
#endif //PLATFORMER_ENGINE_SCENENOTLOADEDEXCEPTION_HPP

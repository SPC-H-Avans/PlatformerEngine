
#ifndef PLATFORMER_ENGINE_LEVELCOULDNOTBEPARSEDEXCEPTION_H
#define PLATFORMER_ENGINE_LEVELCOULDNOTBEPARSEDEXCEPTION_H

#include <stdexcept>

namespace spic {
    class LevelCouldNotBeParsedException : public std::logic_error
    {
    public:
        LevelCouldNotBeParsedException (const std::string& levelName) : std::logic_error{"The level with name: " + levelName + " could not be loaded / parsed!"} {}
    };
}
#endif //PLATFORMER_ENGINE_MAPCOULDNOTBEPARSEDEXCEPTION_H

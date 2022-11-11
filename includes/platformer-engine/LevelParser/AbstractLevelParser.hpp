#ifndef PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP
#define PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP

#include <memory>
#include <string>
#include <map>
#include "GameLevel/GameLevel.hpp"

namespace platformer_engine {
    class AbstractLevelParser {
    public:
        virtual bool Load(const std::string &id, const std::string &filePath, const std::string &fileName) = 0;
    };
}

#endif //PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP

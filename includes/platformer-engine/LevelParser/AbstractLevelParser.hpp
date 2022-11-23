#ifndef PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP
#define PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP

#include <memory>
#include <string>
#include <map>

//#include "GameLevel/GameLevel.hpp"
#include "GameObject.hpp"

namespace platformer_engine {
    class AbstractLevelParser {
    public:
        /**
         * @brief Load a level from a file
         * @param id The id of the level (stored in the map by this id)
         * @param filePath A path to the file (with out the file name)
         * @param fileName Name of the file with the extension
         * @return True if the level was loaded successfully
         */
        virtual auto Load(const std::string &id, const std::string &filePath, const std::string &fileName, const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config) -> bool = 0;

        virtual ~AbstractLevelParser() = default;
    };
}

#endif //PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP

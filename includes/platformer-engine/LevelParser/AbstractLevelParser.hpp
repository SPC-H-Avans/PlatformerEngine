#ifndef PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP
#define PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP

#include <memory>
#include <string>
#include <map>

#include "GameObject.hpp"
#include "Scene.hpp"

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
        virtual auto
        LoadOnScene(spic::Scene &scene, const std::string &id, const std::string &filePath, const std::string &fileName,
                    const std::map<int, std::function<spic::GameObject(spic::Transform)>> &config) -> bool = 0;

        AbstractLevelParser() = default;

        AbstractLevelParser(const AbstractLevelParser &other) = default;

        AbstractLevelParser(AbstractLevelParser &&other) = default;

        AbstractLevelParser &operator=(AbstractLevelParser &&other) = default;

        auto operator=(const AbstractLevelParser &other) -> AbstractLevelParser & = default;

        virtual ~AbstractLevelParser() = default;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_ABSTRACTLEVELPARSER_HPP

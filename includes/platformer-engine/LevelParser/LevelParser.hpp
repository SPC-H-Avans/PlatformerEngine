#ifndef PLATFORMER_ENGINE_LEVELPARSER_HPP
#define PLATFORMER_ENGINE_LEVELPARSER_HPP

#include <string>
#include <map>
#include <memory>
#include "GameLevel/GameLevel.hpp"

namespace platformer_engine {
    class LevelParser {
    public:
        static auto GetInstance() -> LevelParser & {
            static LevelParser s_instance;
            return s_instance;
        }

        LevelParser(LevelParser const &) = delete;

        void operator=(LevelParser const &) = delete;

        /**
         * @brief Load a level from a file
         * @param id The id of the level (stored in the map by this id)
        * @param filePath A path to the file (with out the file name)
        * @param fileName Name of the file with the extension
         */
        bool ParseLevel(const std::string &id, const std::string &filePath, const std::string &fileName);

        /**
         * @brief Get a reference to the level from the map
         * @param id Id of the level
         * @return A reference to the level
         */
        inline auto GetLevel(const std::string &id) -> std::unique_ptr<GameLevel> & { return _levels[id]; }

        /**
         * @brief Get a reference to the map of levels
         * @return The reference to the map of levels
         */
        inline auto GetLevels() -> std::map<std::string, std::unique_ptr<GameLevel>> & { return _levels; }

        /**
         * @brief Clean the map of levels from memory
         */
        void Clean();

    private:
        LevelParser() = default;

        ~LevelParser() = default;

        std::map<std::string, std::unique_ptr<GameLevel>> _levels;
    };
}

#endif //PLATFORMER_ENGINE_LEVELPARSER_HPP

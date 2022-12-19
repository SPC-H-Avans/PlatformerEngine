#ifndef PLATFORMER_ENGINE_LEVELPARSER_HPP
#define PLATFORMER_ENGINE_LEVELPARSER_HPP

#include <string>
#include <map>
#include <memory>
#include <functional>

#include "GameObject.hpp"
#include "Scene.hpp"

namespace platformer_engine {
    class LevelParser {
    public:
        static auto GetInstance() -> LevelParser & {
            static LevelParser s_instance;
            return s_instance;
        }

        LevelParser(LevelParser const &) = delete;

        void operator=(LevelParser const &) = delete;

        LevelParser(LevelParser &&other) = delete;

        LevelParser &operator=(LevelParser &&other) = delete;


        /**
         * @brief Load a level from a file
         * @param id The id of the level (stored in the map by this id)
        * @param filePath A path to the file (with out the file name)
        * @param fileName Name of the file with the extension
         */
        static auto ParseLevel(spic::Scene& scene, const std::string &id, const std::string &filePath, const std::string &fileName, const std::map<int, std::function<spic::GameObject(spic::Transform)>> &config) -> bool;

    private:
        LevelParser() = default;

        ~LevelParser() = default;
    };
}// namespace platformer_engine

#endif //PLATFORMER_ENGINE_LEVELPARSER_HPP

#ifndef PLATFORMER_ENGINE_LEVELPARSER_HPP
#define PLATFORMER_ENGINE_LEVELPARSER_HPP

#include <string>
#include <map>
#include <memory>
#include "GameLevel/GameLevel.hpp"

namespace platformer_engine {
    class LevelParser {
    public:
        static LevelParser &GetInstance() {
            static LevelParser s_instance;
            return s_instance;
        }

        //for singleton
        LevelParser(LevelParser const &) = delete;

        void operator=(LevelParser const &) = delete;

        void ParseLevel(const std::string &id, const std::string &filePath, const std::string &fileName);

        inline std::unique_ptr<GameLevel> &GetLevel(const std::string &id) { return _levels[id]; }

        inline std::map<std::string, std::unique_ptr<GameLevel>> &GetLevels() { return _levels; }

        void Clean();

    private:
        LevelParser() = default;
        std::map<std::string, std::unique_ptr<GameLevel>> _levels;
    };
}

#endif //PLATFORMER_ENGINE_LEVELPARSER_HPP

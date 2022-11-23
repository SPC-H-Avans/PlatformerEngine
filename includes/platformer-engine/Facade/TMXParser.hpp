#ifndef PLATFORMER_ENGINE_TMXPARSER_HPP
#define PLATFORMER_ENGINE_TMXPARSER_HPP

#include <map>
#include <string>
#include <memory>
#include <functional>

#include "GameLevel/GameLevel.hpp"
#include "GameLevel/TileLayer.hpp"
#include "tinyxml.h"
#include "LevelParser/AbstractLevelParser.hpp"
#include "GameObject.hpp"

namespace platformer_engine {

    class TMXParser : public AbstractLevelParser {
    public:
        TMXParser(std::map<std::string, std::unique_ptr<GameLevel>> &levels) : _levels(levels) {};

        auto Load(const std::string &id, const std::string &filePath, const std::string &fileName, const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config) -> bool override;

    private:
        auto ParseLevel(const std::string &id, const std::string &filePath, const std::string &fileName, const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config) -> bool;

        auto ParseTileSet(const TiXmlElement &xmlTileSet) -> TileSet;

        auto
        ParseTileLayer(TiXmlElement &xmlLayer, const std::string &filePath, const TileSetsList &tileSets,
                       const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config,
                       int tileSize, int rowCount, int colCount) -> std::unique_ptr<TileLayer>;

        std::map<std::string, std::unique_ptr<GameLevel>> &_levels;
    };
}

#endif //PLATFORMER_ENGINE_TMXPARSER_HPP

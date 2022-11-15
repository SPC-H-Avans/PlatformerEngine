#ifndef PLATFORMER_ENGINE_TMXPARSER_HPP
#define PLATFORMER_ENGINE_TMXPARSER_HPP

#include <map>
#include <string>
#include <memory>
#include "GameLevel/GameLevel.hpp"
#include "GameLevel/TileLayer.hpp"
#include "tinyxml.h"
#include "LevelParser/AbstractLevelParser.hpp"

namespace platformer_engine {

    class TMXParser : public AbstractLevelParser {
    public:
        TMXParser(std::map<std::string, std::unique_ptr<GameLevel>> &levels) : _levels(levels) {};
        bool Load(const std::string &id, const std::string &filePath, const std::string &fileName);

    private:
        bool ParseLevel(const std::string &id, const std::string &filePath, const std::string &fileName);

        TileSet ParseTileSet(const TiXmlElement &xmlTileSet);

        std::unique_ptr<TileLayer>
        ParseTileLayer(TiXmlElement &xmlLayer, const std::string &filePath, const TileSetsList &tileSets, int tileSize,
                       int rowCount, int colCount);

        std::map<std::string, std::unique_ptr<GameLevel>>& _levels;
    };
}

#endif //PLATFORMER_ENGINE_TMXPARSER_HPP

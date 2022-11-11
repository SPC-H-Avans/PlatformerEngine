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
        TMXParser() = default;
        /**
         * @brief Parse a TMX file and return a GameLevel
         * @return boolean if the parsing was successful
         */
        bool Load(const std::string &id, const std::string &filePath, const std::string &fileName);

        /**
         * @brief Remove level from memory
         * @return
         */

    private:
        bool _parseLevel(const std::string &id, const std::string &filePath, const std::string &fileName);

        TileSet _parseTileSet(const TiXmlElement &xmlTileSet);

        std::unique_ptr<TileLayer>
        _parseTileLayer(TiXmlElement &xmlLayer, const std::string &filePath, const TileSetsList &tileSets, int tileSize,
                       int rowCount, int colCount);
    };
}

#endif //PLATFORMER_ENGINE_TMXPARSER_HPP

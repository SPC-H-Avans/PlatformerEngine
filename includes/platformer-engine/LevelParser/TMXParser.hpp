#ifndef PLATFORMER_ENGINE_TMXPARSER_HPP
#define PLATFORMER_ENGINE_TMXPARSER_HPP

#include <map>
#include <string>
#include <memory>
#include "GameLevel/GameLevel.hpp"
#include "GameLevel/TileLayer.hpp"
#include "tinyxml.h"

namespace platformer_engine {

    class TMXParser {
    public:
        static TMXParser &GetInstance() {
            static TMXParser s_instance;
            return s_instance;
        }

        //for singleton
        TMXParser(TMXParser const &) = delete;

        void operator=(TMXParser const &) = delete;

        /**
         * @brief Parse a TMX file and return a GameLevel
         * @return boolean if the parsing was successful
         */
        bool Load(const std::string &id, const std::string &filePath, const std::string &fileName);

        /**
         * @brief Remove level from memory
         * @return
         */
        void Clean();

        inline std::unique_ptr<GameLevel> &GetLevel(const std::string &id) { return _levels[id]; }

        inline std::map<std::string, std::unique_ptr<GameLevel>> &GetLevels() { return _levels; }

    private:
        TMXParser() {}

        bool _parseLevel(const std::string &id, const std::string &filePath, const std::string &fileName);

        TileSet _parseTileSet(const TiXmlElement &xmlTileSet);

        std::unique_ptr<TileLayer>
        ParseTileLayer(TiXmlElement &xmlLayer, const std::string &filePath, const TileSetsList &tileSets, int tileSize,
                       int rowCount, int colCount);

        std::map<std::string, std::unique_ptr<GameLevel>> _levels;
    };
}

#endif //PLATFORMER_ENGINE_TMXPARSER_HPP

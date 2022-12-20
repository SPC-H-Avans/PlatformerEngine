#ifndef PLATFORMER_ENGINE_TMXPARSER_HPP
#define PLATFORMER_ENGINE_TMXPARSER_HPP

#include <map>
#include <string>
#include <memory>
#include <functional>

#include "tinyxml.h"
#include "LevelParser/AbstractLevelParser.hpp"
#include "GameObject.hpp"

namespace platformer_engine {

    class TMXParser : public AbstractLevelParser {
    public:
        struct TileSet {
            int FirstID, LastID;
            int RowCount, ColCount;
            int TileCount, TileSize;
            std::string Name, Source;
        };
        using TileSetsList = std::vector<TileSet>;
        using TileMap = std::vector<std::vector<int>>;

        auto LoadOnScene(spic::Scene& scene, const std::string &id, const std::string &filePath, const std::string &fileName, const std::map<int, std::function<spic::GameObject(spic::Transform)>> &config) -> bool override;

    private:
        auto ParseLevel(spic::Scene& scene, const std::string &id, const std::string &filePath, const std::string &fileName, const std::map<int, std::function<spic::GameObject(spic::Transform)>> &config) -> bool;

        auto ParseTileSet(const TiXmlElement &xmlTileSet) -> TileSet;

        void ParseTileLayer(spic::Scene& scene, TiXmlElement &xmlLayer, const std::string &filePath,
                            const platformer_engine::TMXParser::TileSetsList &tileSets,
                            int tileSize, int rowCount, int colCount,
                            const std::map<int, std::function<spic::GameObject(spic::Transform)>> &config);
    };
}// namespace platformer_engine

#endif //PLATFORMER_ENGINE_TMXPARSER_HPP

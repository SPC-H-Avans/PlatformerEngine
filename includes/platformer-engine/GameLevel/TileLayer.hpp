#ifndef PLATFORMER_ENGINE_TILELAYER_H
#define PLATFORMER_ENGINE_TILELAYER_H

#include "Layer.hpp"
#include <string>
#include <utility>
#include <vector>

namespace platformer_engine {
    struct TileSet {
        int FirstID, LastID;
        int RowCount, ColCount;
        int TileCount, TileSize;
        std::string Name, Source;
    };

    using TileSetsList = std::vector<TileSet>;
    using TileMap = std::vector<std::vector<int> >;

    class TileLayer : public Layer {
    public:
        TileLayer(int tileSize, int rowCount, int colCount, TileMap  tileMap, TileSetsList  tileSets) :
                _tileSize(tileSize), _rowCount(rowCount), _colCount(colCount), _tileMap(std::move(tileMap)),
                _tileSets(std::move(tileSets)) {}

        virtual void Render();

        virtual void Update();

        inline TileMap GetTileMap() { return _tileMap; }

    private:
        int _tileSize;
        int _rowCount;
        int _colCount;
        TileMap _tileMap;
        TileSetsList _tileSets;
    };
}

#endif //PLATFORMER_ENGINE_TILELAYER_H

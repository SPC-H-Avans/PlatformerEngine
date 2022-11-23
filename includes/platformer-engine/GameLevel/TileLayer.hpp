#ifndef PLATFORMER_ENGINE_TILELAYER_H
#define PLATFORMER_ENGINE_TILELAYER_H

#include <string>
#include <utility>
#include <vector>
#include <functional>

#include "Layer.hpp"
#include "GameObject.hpp"

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
        TileLayer(const std::string &filePath, int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetsList tileSets,
                  const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config);

        void Render() override;

        void Update() override;

        inline auto GetTileMap() -> TileMap { return _tileMap; }

    private:
        int _tileSize;
        int _rowCount;
        int _colCount;
        TileMap _tileMap;
        TileSetsList _tileSets;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_TILELAYER_H

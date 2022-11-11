#ifndef PLATFORMER_ENGINE_LEVEL_H
#define PLATFORMER_ENGINE_LEVEL_H

#include "Layer.hpp"
#include <vector>
#include <memory>

const int DEFAULT_BASE_TILE_SIZE = 32;
const int DEFAULT_ROW_COUNT = 20;
const int DEFAULT_COL_COUNT = 30;

namespace platformer_engine {
    class GameLevel {
    public:
        GameLevel() = default;

        void Render() {
            for (auto &_mapLayer: _mapLayers)
                _mapLayer->Render();
        }

        void Update() {
            for (auto &_mapLayer: _mapLayers)
                _mapLayer->Update();
        }

        auto GetMapLayer() -> std::vector<std::unique_ptr<Layer>>& {
            return _mapLayers;
        }

        int BaseTileSize = DEFAULT_BASE_TILE_SIZE;
        int RowCount = DEFAULT_ROW_COUNT;
        int ColCount = DEFAULT_COL_COUNT;

    private:
        friend class TMXParser;

        std::vector<std::unique_ptr<Layer>> _mapLayers;
    };
}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_LEVEL_H

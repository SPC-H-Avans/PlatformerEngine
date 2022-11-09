#ifndef PLATFORMER_ENGINE_LEVEL_H
#define PLATFORMER_ENGINE_LEVEL_H

#include <vector>
#include "TMXParser/Layer.hpp"

class Level {
public:
    Level() {}

    void Render() {
        for (unsigned int i = 0; i < mapLayers.size(); i++)
            mapLayers[i]->render();
    }

    void Update() {
        for (unsigned int i = 0; i < mapLayers.size(); i++)
            mapLayers[i]->update();
    }

    std::vector<Layer *> GetLayers() {
        return mapLayers;
    }

    int baseTileSize = 32;
    int RowCount = 20;
    int ColCount = 30;

private:
    friend class MapParser;

    std::vector<Layer *> mapLayers;
};


#endif //PLATFORMER_ENGINE_LEVEL_H

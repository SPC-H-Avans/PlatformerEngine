#ifndef PLATFORMER_ENGINE_LEVEL_H
#define PLATFORMER_ENGINE_LEVEL_H

#include <vector>
#include "TMXParser/Layer.h"

class Level {
public:
    Level() {}

    void render() {
        for (unsigned int i = 0; i < mapLayers.size(); i++)
            mapLayers[i]->render();
    }

    void update() {
        for (unsigned int i = 0; i < mapLayers.size(); i++)
            mapLayers[i]->update();
    }

    std::vector<Layer *> getLayers() {
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

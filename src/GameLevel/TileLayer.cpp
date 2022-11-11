#include "GameLevel/TileLayer.hpp"
#include "Texture/TextureManager.hpp"

void platformer_engine::TileLayer::Render() {
    for(unsigned int i = 0; i < _rowCount; i++){
        for(unsigned int j = 0; j < _colCount; j++){

            int tileID = _tileMap[i][j];

            if(tileID == 0)
                continue;

                int index = 0;
                if(_tileSets.size() > 1){
                    for(unsigned int k = 1; k < _tileSets.size(); k++){
                        if(tileID > _tileSets[k].FirstID && tileID < _tileSets[k].LastID){
                            tileID = tileID + _tileSets[k].TileCount - _tileSets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }

                TileSet ts = _tileSets[index];
                int tileRow = tileID/ts.ColCount;
                int tileCol = tileID - tileRow*ts.ColCount-1;

                // if this tile is on the las column
                if(tileID % ts.ColCount == 0){
                    tileRow--;
                    tileCol = ts.ColCount - 1;
                }

                TextureManager::GetInstance().DrawTile(ts.Name, ts.TileSize, j*ts.TileSize, i*ts.TileSize, tileRow, tileCol);
        }
    }
}

void platformer_engine::TileLayer::Update() {

}

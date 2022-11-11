#include "LevelParser/TMXParser.hpp"

bool
platformer_engine::TMXParser::Load(const std::string &id, const std::string &filePath, const std::string &fileName) {
    bool result = _parseLevel(id, filePath, fileName);

    if (result == false) {
        std::cout << "Failed to parse level: " << id << std::endl;
    }
    return result;
}

bool platformer_engine::TMXParser::_parseLevel(const std::string &id, const std::string &filePath,
                                               const std::string &fileName) {
    TiXmlDocument xml;
    xml.LoadFile(filePath + fileName);

    if (xml.Error()) {
        std::cerr << "Failed to load: " << filePath << fileName << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();

    int colCount, rowCount, tileSize = 0;
    root->Attribute("width", &colCount);
    root->Attribute("height", &rowCount);
    root->Attribute("tilewidth", &tileSize);

    std::unique_ptr<GameLevel> gameLevel = std::make_unique<GameLevel>();

    // Parse Tile sets
    TileSetsList tileSets;

    //TinyXML deletes the nodes that they add in memory itself
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            tileSets.emplace_back(std::move(_parseTileSet(*e)));
        }
//        if (e->Value() == std::string("layer")) {
//            std::unique_ptr<TileLayer> tileLayer = ParseTileLayer(*e, tileSets, tileSize, rowCount, colCount);
//            gameLevel->_mapLayers.emplace_back(std::move(tileLayer));
//        }
    }

    // Parse Layers
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            std::unique_ptr<TileLayer> tileLayer = ParseTileLayer(*e, filePath, tileSets, tileSize, rowCount, colCount);
            gameLevel->_mapLayers.push_back(std::move(tileLayer));
        }
    }
    gameLevel->BaseTileSize = tileSize;
    gameLevel->RowCount = rowCount;
    gameLevel->ColCount = colCount;

    _levels[id] = std::move(gameLevel);

    return true;
}

platformer_engine::TileSet platformer_engine::TMXParser::_parseTileSet(const TiXmlElement &xmlTileSet) {
    TileSet tileSet;

    tileSet.Name = xmlTileSet.Attribute("name");
    xmlTileSet.Attribute("firstgid", &tileSet.FirstID);
    xmlTileSet.Attribute("tilecount", &tileSet.TileCount);
    tileSet.LastID = (tileSet.FirstID + tileSet.TileCount) - 1;

    xmlTileSet.Attribute("columns", &tileSet.ColCount);
    tileSet.RowCount = tileSet.TileCount / tileSet.ColCount;
    xmlTileSet.Attribute("tilewidth", &tileSet.TileSize);

    const TiXmlElement *image = xmlTileSet.FirstChildElement();
    tileSet.Source = image->Attribute("source");

    return tileSet;
}

std::unique_ptr<platformer_engine::TileLayer>
platformer_engine::TMXParser::ParseTileLayer(TiXmlElement &xmlLayer, const std::string &filePath,
                                             const platformer_engine::TileSetsList &tileSets,
                                             int tileSize, int rowCount,
                                             int colCount) {
    TiXmlElement *data;
    for (TiXmlElement *e = xmlLayer.FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            data = e;
            break;
        }
    }

    // Parse Layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tileMap(rowCount, std::vector<int>(colCount, 0));

    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < colCount; col++) {
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tileMap[row][col];

            if (!iss.good())
                break;
        }
    }

    return std::make_unique<TileLayer>(filePath, tileSize, rowCount, colCount, tileMap, tileSets);
}

void platformer_engine::TMXParser::Clean() {
    std::map<std::string, std::unique_ptr<GameLevel>>::iterator it;
    for (it = _levels.begin(); it != _levels.end(); it++)
        it->second = nullptr;

    _levels.clear();
}
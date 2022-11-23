#include "Facade/TMXParser.hpp"
#include "LevelParser/LevelParser.hpp"
#include "Debug.hpp"
#include "Engine/Engine.hpp"

bool platformer_engine::TMXParser::Load(const std::string &id, const std::string &filePath, const std::string &fileName,
                                   const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config) {
    bool result = ParseLevel(id, filePath, fileName, config);

    if (!result) {
        spic::Debug::LogWarning( "Failed to parse level: " + id);
    }
    return result;
}

bool platformer_engine::TMXParser::ParseLevel(const std::string &id, const std::string &filePath, const std::string &fileName,
                                              const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config) {
    TiXmlDocument xml;
    xml.LoadFile(filePath + fileName);

    if (xml.Error()) {
        spic::Debug::LogWarning("Failed to load: " + filePath + fileName);
        return false;
    }

    TiXmlElement *root = xml.RootElement();

    int colCount, rowCount, tileSize = 0; // col/row not initialized?
    root->Attribute("width", &colCount);
    root->Attribute("height", &rowCount);
    root->Attribute("tilewidth", &tileSize);

    std::unique_ptr<GameLevel> gameLevel = std::make_unique<GameLevel>();

    // Parse Tile sets
    TileSetsList tileSets;

    //TinyXML deletes the nodes that they add in memory itself
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            tileSets.emplace_back(std::move(ParseTileSet(*e)));
        }
    }

    // Parse Layers
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            std::unique_ptr<TileLayer> tileLayer = ParseTileLayer(*e, filePath, tileSets, config, tileSize, rowCount, colCount);
            gameLevel->_mapLayers.push_back(std::move(tileLayer));
        }
    }
    gameLevel->BaseTileSize = tileSize;
    gameLevel->RowCount = rowCount;
    gameLevel->ColCount = colCount;

    platformer_engine::Engine& engine = platformer_engine::Engine::GetInstance(); // maybe let the director add them to the scene instead
    std::unique_ptr<Scene>& scene =  engine.GetActiveScene();

    _levels[id] = std::move(gameLevel);

    return true;
}

platformer_engine::TileSet platformer_engine::TMXParser::ParseTileSet(const TiXmlElement &xmlTileSet) {
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
                                             const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config,
                                             int tileSize, int rowCount, int colCount) {
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

    std::cout << id << "\n";
//    for (int row = 0; row < rowCount; row++) {
//        for (int col = 0; col < colCount; col++) {
//            getline(iss, id, ',');
//            std::stringstream convertor(id);
//            convertor >> tileMap[row][col];
//
//            if (!iss.good())
//                break;
//        }
//    }

    return std::make_unique<TileLayer>(filePath, tileSize, rowCount, colCount, tileMap, tileSets);
}
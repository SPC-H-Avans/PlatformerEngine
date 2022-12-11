#include "Facade/TMXParser.hpp"
#include "LevelParser/LevelParser.hpp"
#include "Debug.hpp"
#include "Engine/Engine.hpp"

auto platformer_engine::TMXParser::LoadOnScene(spic::Scene& scene, const std::string &id, const std::string &filePath, const std::string &fileName,
                                        const std::map<int, std::function<spic::GameObject&(Transform)>> &config) -> bool {
    bool result = ParseLevel(scene, id, filePath, fileName, config);

    if (!result) {
        spic::Debug::LogWarning( "Failed to parse level: " + id);
    }
    return result;
}

auto platformer_engine::TMXParser::ParseLevel(spic::Scene& scene, const std::string &id, const std::string &filePath, const std::string &fileName,
                                              const std::map<int, std::function<spic::GameObject&(Transform)>> &config) -> bool {
    TiXmlDocument xml;
    xml.LoadFile(filePath + fileName);

    if (xml.Error()) {
        spic::Debug::LogWarning("Failed to load: " + filePath + fileName);
        return false;
    }

    TiXmlElement *root = xml.RootElement();

    int colCount = 0, rowCount = 0, tileSize = 0;
    root->Attribute("width", &colCount);
    root->Attribute("height", &rowCount);
    root->Attribute("tilewidth", &tileSize);

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
            ParseTileLayer(scene, *e, filePath, tileSets, tileSize, rowCount, colCount, config);
        }
    }

    return true;
}

auto platformer_engine::TMXParser::ParseTileSet(const TiXmlElement &xmlTileSet) -> platformer_engine::TMXParser::TileSet {
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

void platformer_engine::TMXParser::ParseTileLayer(spic::Scene& scene, TiXmlElement &xmlLayer, const std::string &filePath,
                                                  const platformer_engine::TMXParser::TileSetsList &tileSets,
                                                  int tileSize, int rowCount, int colCount,
                                                  const std::map<int, std::function<spic::GameObject&(Transform)>> &config) {
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

            // if tile key exists in config, do the method
            if (config.find(tileMap[row][col]) != config.end()) {
                auto transform = Transform {
                    Point {
                        static_cast<float>(col * tileSize),
                        static_cast<float>(row * tileSize)},
                    0, 1.0 };

                GameObject& object = config.at(tileMap[row][col])(transform); // create the tile
                scene.AddObject(std::make_unique<GameObject>(object));
            }
            if (!iss.good())
                break;
        }
    }
}
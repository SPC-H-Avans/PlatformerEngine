#ifndef PLATFORMER_ENGINE_MAPPARSER_HPP
#define PLATFORMER_ENGINE_MAPPARSER_HPP

class MapParser
{
public:
    static MapParser& GetInstance()
    {
        static MapParser s_instance;
        return s_instance;
    }

    //for singleton
    MapParser(MapParser const&) = delete;
    void operator=(MapParser const&) = delete;

    bool load();
    void clean();

//    inline GameMap* GetMap(std::string id){return m_MapDict[id];}
//    inline static MapParser* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new MapParser();}
//
private:
    MapParser(){}
//
//    bool Parse(std::string id, std::string source);
//    Tileset ParseTileset(TiXmlElement* xmlTileset);
//    TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount);
//
//    static MapParser* s_Instance;
//    std::map<std::string, GameMap*> m_MapDict;
};

#endif //PLATFORMER_ENGINE_MAPPARSER_HPP

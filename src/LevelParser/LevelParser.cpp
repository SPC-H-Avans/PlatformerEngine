#include "LevelParser/LevelParser.hpp"
#include "Facade/TMXParser.hpp"
#include "Debug.hpp"

namespace platformer_engine {
    void LevelParser::ParseLevel(const std::string &id, const std::string &filePath, const std::string &fileName) {

        std::string fileType = fileName.substr(fileName.find(".") + 1);

        if (fileType == "tmx") {
            TMXParser parser = TMXParser();
            parser.Load(id, filePath, fileName);
        } else {
            spic::Debug::LogWarning("No LevelParser defined for filetype: " + fileType);
        }
    }
}

void platformer_engine::LevelParser::Clean() {
    std::map<std::string, std::unique_ptr<GameLevel>>::iterator it;
    for (it = _levels.begin(); it != _levels.end(); it++)
        it->second = nullptr;

    _levels.clear();
}

#include "LevelParser/LevelParser.hpp"
#include "Facade/TMXParser.hpp"
#include "Debug.hpp"
#include "Exceptions/LevelCouldNotBeParsedException.hpp"

namespace platformer_engine {
    bool LevelParser::ParseLevel(const std::string &id, const std::string &filePath, const std::string &fileName) {
        std::string fileType = fileName.substr(fileName.find('.') + 1);

        if (fileType == "tmx") {
            auto parser = TMXParser(_levels);
            return parser.Load(id, filePath, fileName);
        } else {
            throw spic::LevelCouldNotBeParsedException(filePath + fileName);
        }
    }
}

void platformer_engine::LevelParser::Clean() {
    std::map<std::string, std::unique_ptr<GameLevel>>::iterator it;
    for (it = _levels.begin(); it != _levels.end(); it++)
        it->second = nullptr;

    _levels.clear();
}

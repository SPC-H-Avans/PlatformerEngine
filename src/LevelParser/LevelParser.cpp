#include "LevelParser/LevelParser.hpp"
#include "Facade/TMXParser.hpp"
#include "Debug.hpp"
#include "Exceptions/LevelCouldNotBeParsedException.hpp"

namespace platformer_engine {
    auto LevelParser::ParseLevel(const std::string &id, const std::string &filePath, const std::string &fileName,
                                 const std::map<int, std::function<std::shared_ptr<spic::GameObject>()>> &config) -> bool {
        std::string fileType = fileName.substr(fileName.find('.') + 1);

        if (fileType == "tmx") {
            auto parser = TMXParser(/*_levels*/);  // can be made static instead of using a singleton after removing _levels
            return parser.Load(id, filePath, fileName, config);
        } else {
            throw spic::LevelCouldNotBeParsedException(filePath + fileName);
        }
    }
}

//void platformer_engine::LevelParser::Clean() {
//    std::map<std::string, std::unique_ptr<GameLevel>>::iterator it;
//    for (it = _levels.begin(); it != _levels.end(); it++)
//        it->second = nullptr;
//
//    _levels.clear();
//}

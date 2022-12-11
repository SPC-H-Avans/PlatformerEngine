#include "LevelParser/LevelParser.hpp"
#include "Facade/TMXParser.hpp"
#include "Debug.hpp"
#include "Exceptions/LevelCouldNotBeParsedException.hpp"

namespace platformer_engine {
    auto LevelParser::ParseLevel(spic::Scene& scene, const std::string &id, const std::string &filePath, const std::string &fileName,
                                 const std::map<int, std::function<spic::GameObject&(spic::Transform)>> &config) -> bool {
        std::string fileType = fileName.substr(fileName.find('.') + 1);

        if (fileType == "tmx") {
            auto parser = TMXParser();  // can be made static instead of using a singleton after removing _levels
            return parser.LoadOnScene(scene, id, filePath, fileName, config);
        } else {
            throw spic::LevelCouldNotBeParsedException(filePath + fileName);
        }
    }
}

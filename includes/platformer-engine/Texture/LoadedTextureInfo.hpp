#ifndef PLATFORMER_ENGINE_LOADEDTEXTUREINFO_HPP
#define PLATFORMER_ENGINE_LOADEDTEXTUREINFO_HPP

#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

namespace platformer_engine {
    class LoadedTextureInfo {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & _textureId;
            ar & _texturePath;
        }

        LoadedTextureInfo() = default;

        LoadedTextureInfo(const std::string &textureId, const std::string &texturePath);

        inline auto GetTextureId() -> std::string { return _textureId; };

        inline auto GetTexturePath() -> std::string { return _texturePath; };

    private:
        std::string _textureId;
        std::string _texturePath;
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_LOADEDTEXTUREINFO_HPP

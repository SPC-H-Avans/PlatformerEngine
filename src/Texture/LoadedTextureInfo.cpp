#include "Texture/LoadedTextureInfo.hpp"

platformer_engine::LoadedTextureInfo::LoadedTextureInfo(std::string textureId, std::string texturePath)
        : _textureId(std::move(textureId)), _texturePath(std::move(texturePath)) {
}

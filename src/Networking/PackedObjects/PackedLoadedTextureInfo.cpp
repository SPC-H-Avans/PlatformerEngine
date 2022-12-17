#include "Networking/PackedObjects/PackedLoadedTextureInfo.hpp"
#include "Texture/TextureManager.hpp"

void platformer_engine::PackedLoadedTextureInfo::LoadTextures() {
    _loadedTextureInfos = TextureManager::GetInstance().GetLoadedTextures();
}

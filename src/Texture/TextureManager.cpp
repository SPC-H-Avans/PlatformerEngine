#include <utility>

#include "Texture/TextureManager.hpp"

auto platformer_engine::TextureManager::LoadTexture(const std::string &id, const std::string &fileName) -> bool {
    return _graphicsFacade->LoadTexture(id, fileName);
}

void
platformer_engine::TextureManager::DrawTexture(const std::string &id, int x, int y, int width, int height,
                                               const SPIC_RendererFlip &flip, double scale) {
    _graphicsFacade->DrawTexture(id, x, y, width, height, flip, scale);
}

void platformer_engine::TextureManager::DrawTile(const std::string &tileSetID, int tileSize, int x, int y, int row, int frame,
                                                 const platformer_engine::SPIC_RendererFlip &flip, double scale) {
    _graphicsFacade->DrawTile(tileSetID, tileSize, x, y, row, frame, flip, scale);
}

void
platformer_engine::TextureManager::DrawFrame(const std::string &id, int x, int y, int width, int height, int row, int frame,
                                             const platformer_engine::SPIC_RendererFlip &flip, double scale) {
    _graphicsFacade->DrawFrame(id, x, y, width, height, row, frame, flip, scale);
}


void platformer_engine::TextureManager::Remove(const std::string &id) {

}

void platformer_engine::TextureManager::ClearTextures() {
    _graphicsFacade->ClearTextures();
}
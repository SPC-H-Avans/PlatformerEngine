#include <utility>

#include "Texture/TextureManager.hpp"

auto platformer_engine::TextureManager::LoadTexture(const std::string &id, const std::string &fileName) -> bool {
    return GraphicsFacade::GetInstance().LoadTexture(id, fileName);
}

void
platformer_engine::TextureManager::DrawTexture(const std::string &id, int x, int y, int width, int height,
                                               const SPIC_RendererFlip &flip, double scale,
                                               int spriteSheetX, int spriteSheetY) {
    GraphicsFacade::GetInstance().DrawTexture(id, x, y, width, height, flip, scale, spriteSheetX, spriteSheetY);
}

void platformer_engine::TextureManager::DrawUIText(const std::string textId, const int x, const int y, const int width, const int height) {
    GraphicsFacade::GetInstance().DrawUIText(textId, x, y, width, height);
}

void
platformer_engine::TextureManager::DrawFrame(const std::string &id, int x, int y, int width, int height, int row, int frame,
                                             const platformer_engine::SPIC_RendererFlip &flip, double scale) {
    GraphicsFacade::GetInstance().DrawFrame(id, x, y, width, height, row, frame, flip, scale);
}


void platformer_engine::TextureManager::Remove(const std::string &id) {

}

void platformer_engine::TextureManager::ClearTextures() {
    GraphicsFacade::GetInstance().ClearTextures();
}
#include <utility>

#include "Texture/TextureManager.hpp"
#include "Engine/Engine.hpp"

auto platformer_engine::TextureManager::LoadTexture(const std::string &id, const std::string &fileName) -> bool {
    return _graphicsFacade->LoadTexture(id, fileName);
}

void
platformer_engine::TextureManager::DrawTexture(const std::string &id, int x, int y, int width, int height,
                                               const SPIC_RendererFlip &flip, double scale) {
    Transform camera = GetCameraPosition();
    _graphicsFacade->DrawTexture(id, (x - camera.position.x), (y - camera.position.y), width, height, flip, scale);
}

void platformer_engine::TextureManager::DrawTile(const std::string &tileSetID, int tileSize, int x, int y, int row, int frame,
                                                 const platformer_engine::SPIC_RendererFlip &flip, double scale) {
    Transform camera = GetCameraPosition();
    _graphicsFacade->DrawTile(tileSetID, tileSize, (x - camera.position.x), (y - camera.position.y), row, frame, flip, scale);
}

void
platformer_engine::TextureManager::DrawFrame(const std::string &id, int x, int y, int width, int height, int row, int frame,
                                             const platformer_engine::SPIC_RendererFlip &flip, double scale) {
    Transform camera = GetCameraPosition();
    _graphicsFacade->DrawFrame(id, (x - camera.position.x), (y - camera.position.y), width, height, row, frame, flip, scale);
}


void platformer_engine::TextureManager::Remove(const std::string &id) {
}

void platformer_engine::TextureManager::ClearTextures() {
    _graphicsFacade->ClearTextures();
}

spic::Transform platformer_engine::TextureManager::GetCameraPosition() {
    Engine &engine = Engine::GetInstance();
    auto camera = engine.GetActiveScene().GetActiveCamera();

    if(camera != nullptr){
        return camera->GetTarget(engine.GetWindow().GetWidth(), engine.GetWindow().GetHeight());
    }

    return Transform { 0, 0};
}

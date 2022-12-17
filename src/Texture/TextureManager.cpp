#include "Texture/TextureManager.hpp"
#include "Engine/Engine.hpp"

auto platformer_engine::TextureManager::LoadTexture(const std::string &id, const std::string &fileName) -> bool {
    auto result = GraphicsFacade::GetInstance().LoadTexture(id, fileName);
    if (result) {
        _loadedTextures.emplace_back(id, fileName);
    }
    return result;
}

auto platformer_engine::TextureManager::CreateOrUpdateUIText(const std::string textId, const std::string filePath,
                                                             const std::string text, const int fontSize,
                                                             const spic::Color color) -> bool {
    auto result = GraphicsFacade::GetInstance().CreateOrUpdateUIText(textId, filePath, text, fontSize, color);
//    if (result) { // UI objects should only be seen by the client
//        _loadedTextures.emplace_back(textId, filePath);
//    }
    return result;
}

void
platformer_engine::TextureManager::DrawTexture(const std::string &id, int x, int y, int width, int height,
                                               const SPIC_RendererFlip &flip, double scale,
                                               int spriteSheetX, int spriteSheetY) {
    Transform camera = GetCameraPosition();
    GraphicsFacade::GetInstance().DrawTexture(id, (x - camera.position.x), (y - camera.position.y), width, height, flip,
                                              scale, spriteSheetX, spriteSheetY);
}

void platformer_engine::TextureManager::DrawUIButton(const std::string &id, int x, int y, int width, int height,
                                                     const SPIC_RendererFlip &flip, double scale,
                                                     int spriteSheetX, int spriteSheetY) {
    GraphicsFacade::GetInstance().DrawTexture(id, x, y, width, height, flip, scale, spriteSheetX, spriteSheetY);
}

void platformer_engine::TextureManager::DrawUIText(const std::string textId, const int x, const int y, const int width,
                                                   const int height) {
    GraphicsFacade::GetInstance().DrawUIText(textId, x, y, width, height);
}

void
platformer_engine::TextureManager::DrawFrame(const std::string &id, int x, int y, int width, int height, int row,
                                             int frame, const platformer_engine::SPIC_RendererFlip &flip,
                                             double scale) {
    Transform camera = GetCameraPosition();
    GraphicsFacade::GetInstance().DrawFrame(id, (x - camera.position.x), (y - camera.position.y), width, height, row,
                                            frame, flip,
                                            camera.scale);
}

spic::Transform platformer_engine::TextureManager::GetCameraPosition() {
    Engine &engine = Engine::GetInstance();
    auto camera = engine.GetActiveScene().GetActiveCamera();

    if (camera != nullptr) {
        return camera->GetTarget(engine.GetWindow().GetWidth(), engine.GetWindow().GetHeight());
    }

    return Transform{0, 0};
}

void platformer_engine::TextureManager::ClearTextures() {
    GraphicsFacade::GetInstance().ClearTextures();
    _loadedTextures.clear();
}
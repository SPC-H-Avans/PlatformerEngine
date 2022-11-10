#include <utility>

#include "Texture/TextureManager.hpp"

bool platformer_engine::TextureManager::Load(std::string id, std::string fileName) {
    return _graphicsFacade->Load(std::move(id), std::move(fileName));
}

void
platformer_engine::TextureManager::Draw(std::string id, int x, int y, int width, int height, SPIC_RendererFlip flip) {

}

void platformer_engine::TextureManager::Remove(std::string id) {

}

void platformer_engine::TextureManager::Clear() {

}
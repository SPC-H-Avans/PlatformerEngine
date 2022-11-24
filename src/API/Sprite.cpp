#include "Sprite.hpp"

#include <utility>

spic::Sprite::Sprite(std::string  spriteId, int sortingLayer, int orderInLayer, int spriteWidth, int spriteHeight,
                     platformer_engine::SPIC_RendererFlip flip, spic::Color color,
                     double spriteScale, int spriteSheetRow, int spriteSheetCol) :
        _spriteId(std::move(spriteId)), _sortingLayer(sortingLayer), _orderInLayer(orderInLayer), _spriteWidth(spriteWidth), _spriteHeight(spriteHeight),
        _flip(flip), _color(color),
        _spriteScale(spriteScale), _spriteSheetRow(spriteSheetRow), _spriteSheetCol(spriteSheetCol) {
}

void spic::Sprite::Render(spic::Transform transform) {
    platformer_engine::TextureManager& textureManager = platformer_engine::TextureManager::GetInstance();
    textureManager.DrawTexture(_spriteId, transform.position.x, transform.position.y, _spriteWidth, _spriteHeight, _flip, _spriteScale);
}
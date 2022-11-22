#include "Sprite.hpp"

#include <utility>

spic::Sprite::Sprite(std::string  spriteId, int sortingLayer, int orderInLayer, int spriteWidth,
                     int spriteHeight, platformer_engine::SPIC_RendererFlip flip, spic::Color color, double spriteScale): _spriteId(std::move(spriteId)), _flip(flip), _sortingLayer(sortingLayer), _orderInLayer(orderInLayer), _spriteWidth(spriteWidth), _spriteHeight(spriteHeight),
                                                     _color(color), _spriteScale(spriteScale) {
}

void spic::Sprite::Render(spic::Transform transform) {
   platformer_engine::TextureManager& textureManager = platformer_engine::TextureManager::GetInstance();
    textureManager.DrawTexture(_spriteId, transform.position.x, transform.position.y, _spriteWidth, _spriteHeight, _flip, _spriteScale);
}
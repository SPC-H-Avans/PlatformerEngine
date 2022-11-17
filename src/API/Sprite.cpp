#include "Sprite.hpp"

#include <utility>

spic::Sprite::Sprite(std::string  spriteId, int sortingLayer, int orderInLayer, int spriteWidth,
                     int spriteHeight, platformer_engine::SPIC_RendererFlip flip, spic::Color color, double spriteScale): _spriteId(std::move(spriteId)), _flip(flip), _sortingLayer(sortingLayer), _orderInLayer(orderInLayer), _spriteWidth(spriteWidth), _spriteHeight(spriteHeight),
                                                     _color(color), _spriteScale(spriteScale) {
}

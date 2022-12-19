#include "Sprite.hpp"
#include <boost/serialization/export.hpp>
#include <utility>

spic::Sprite::Sprite(std::string spriteId, int spriteWidth, int spriteHeight, int sortingLayer, int orderInLayer,
                     platformer_engine::SPIC_RendererFlip flip, spic::Color color,
                     double spriteScale, int spriteSheetX, int spriteSheetY) :
        _spriteId(std::move(spriteId)), _spriteWidth(spriteWidth), _spriteHeight(spriteHeight),
        _sortingLayer(sortingLayer), _orderInLayer(orderInLayer),
        _flip(flip), _color(color),
        _spriteScale(spriteScale), _spriteSheetX(spriteSheetX), _spriteSheetY(spriteSheetY) {
}

void spic::Sprite::Render(spic::Transform transform) {
    platformer_engine::TextureManager &textureManager = platformer_engine::TextureManager::GetInstance();
    textureManager.DrawTexture(_spriteId, transform.position.x, transform.position.y, _spriteWidth, _spriteHeight,
                               _flip, _spriteScale, transform.rotation, _spriteSheetX, _spriteSheetY);
}

BOOST_CLASS_EXPORT_IMPLEMENT(spic::Sprite);
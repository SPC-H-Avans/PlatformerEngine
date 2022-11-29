#include <utility>

#include "Texture/AnimatedSprite.hpp"

#define ROTATION_TO_FLIP 180.0f

platformer_engine::AnimatedSprite::AnimatedSprite(std::string spriteId, int sortingLayer,
                                                  int orderInLayer, int spriteWidth, int spriteHeight,
                                                  int frameCount, int animationSpeed, int spriteRow, platformer_engine::SPIC_RendererFlip flip, spic::Color color, double spriteScale)
        : _frameCount(frameCount), _animationSpeed(animationSpeed), _currentFrame(0), _spriteRow(spriteRow), Sprite(std::move(spriteId), sortingLayer, orderInLayer, spriteWidth, spriteHeight, flip, color, spriteScale) {

}

auto platformer_engine::AnimatedSprite::operator=(const platformer_engine::AnimatedSprite &other) -> platformer_engine::AnimatedSprite& {
    _frameCount = other._frameCount;
    _animationSpeed = other._animationSpeed;
    _spriteRow = other._spriteRow;
    _spriteId = other._spriteId;
//    _sortingLayer = other._sortingLayer;
//    _orderInLayer = other._orderInLayer;
//spriteWidth, spriteHeight, flip, color, spriteScale
    _spriteWidth = other._spriteWidth;
    _spriteHeight = other._spriteHeight;
//    _flip = other._flip;
//    _color = other._color;
    _spriteScale = other._spriteScale;
    return *this;
}

void platformer_engine::AnimatedSprite::Update() {
    _currentFrame = (static_cast<int>(platformer_engine::Window::GetTicks())/_animationSpeed) % _frameCount;
}

void platformer_engine::AnimatedSprite::Draw(spic::Transform transform) {
    SPIC_RendererFlip flip = FLIP_NONE;
    if(transform.rotation == ROTATION_TO_FLIP || transform.rotation == ROTATION_TO_FLIP * -1){
        flip = FLIP_HORIZONTAL;
    }
    TextureManager::GetInstance().DrawFrame(_spriteId, static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), _spriteWidth, _spriteHeight, _spriteRow, _currentFrame, flip, transform.scale * GetSpriteScale());
}

void platformer_engine::AnimatedSprite::ResetCurrentFrame() {
    _currentFrame = 0;
}

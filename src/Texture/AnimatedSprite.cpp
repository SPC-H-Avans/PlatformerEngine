#include <utility>

#include "Texture/AnimatedSprite.hpp"

#define ROTATION_TO_FLIP 180.0f

platformer_engine::AnimatedSprite::AnimatedSprite(std::string spriteId, int spriteWidth, int spriteHeight,
                                                  int frameCount, int sortingLayer, int orderInLayer,
                                                  int animationSpeed, int spriteRow,
                                                  platformer_engine::SPIC_RendererFlip flip, spic::Color color,
                                                  double spriteScale)
        : _frameCount(frameCount), _animationSpeed(animationSpeed), _currentFrame(0), _spriteRow(spriteRow),
          Sprite(std::move(spriteId), spriteWidth, spriteHeight, sortingLayer, orderInLayer, flip, color, spriteScale) {

}

void platformer_engine::AnimatedSprite::Update(double speedMultiplier) {
    _currentFrame = (static_cast<int>((platformer_engine::Window::GetTicks()) / (_animationSpeed / speedMultiplier))) % _frameCount;
}

void platformer_engine::AnimatedSprite::Draw(spic::Transform transform) {
    SPIC_RendererFlip flip = FLIP_NONE;
    if (transform.rotation == ROTATION_TO_FLIP || transform.rotation == ROTATION_TO_FLIP * -1) {
        flip = FLIP_HORIZONTAL;
    }
    TextureManager::GetInstance().DrawFrame(_spriteId, static_cast<int>(transform.position.x),
                                            static_cast<int>(transform.position.y), _spriteWidth, _spriteHeight,
                                            _spriteRow, _currentFrame, flip, transform.scale * GetSpriteScale());
}

void platformer_engine::AnimatedSprite::ResetCurrentFrame() {
    _currentFrame = 0;
}

platformer_engine::AnimatedSprite::AnimatedSprite() {}

BOOST_CLASS_EXPORT(platformer_engine::AnimatedSprite);

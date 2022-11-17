#include <utility>

#include "Texture/AnimatedSprite.hpp"

platformer_engine::AnimatedSprite::AnimatedSprite(std::string spriteId, int sortingLayer,
                                                  int orderInLayer, int spriteWidth, int spriteHeight,
                                                  int frameCount, int animationSpeed, int spriteRow, platformer_engine::SPIC_RendererFlip flip, spic::Color color)
        : _frameCount(frameCount), _animationSpeed(animationSpeed), _currentFrame(0), _spriteRow(spriteRow), Sprite(std::move(spriteId), sortingLayer, orderInLayer, spriteWidth, spriteHeight, flip, color) {

}

void platformer_engine::AnimatedSprite::Update() {
    _currentFrame = (static_cast<int>(platformer_engine::Window::GetTicks())/_animationSpeed) % _frameCount;
}

void platformer_engine::AnimatedSprite::Draw(spic::Transform transform) {
    SPIC_RendererFlip flip = FLIP_NONE;
    if(transform.rotation == 180.0f || transform.rotation == -180.0f){
        flip = FLIP_HORIZONTAL;
    }
    TextureManager::GetInstance().DrawFrame(_spriteId, static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), _spriteWidth, _spriteHeight, _spriteRow, _currentFrame, FLIP_NONE);
}

void platformer_engine::AnimatedSprite::ResetCurrentFrame() {
    _currentFrame = 0;
}

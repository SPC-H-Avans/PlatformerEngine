#include "Animator.hpp"

spic::Animator::Animator(const std::shared_ptr<platformer_engine::AnimatedSprite> &animatedSprite, bool isPlaying,
                         bool isLooping) : _isPlaying(isPlaying), _isLooping(isLooping),
                                           _currentAnimation(animatedSprite) {
    AddAnimation(animatedSprite);
}

void spic::Animator::AddAnimation(const std::shared_ptr<platformer_engine::AnimatedSprite> &animatedSprite) {
    _animationMap[animatedSprite->GetSpriteId()] = animatedSprite;
    if (_currentAnimation == nullptr) {
        _currentAnimation = animatedSprite;
    }
}

void spic::Animator::SetActiveAnimation(const std::string &animationId) {
    if (_animationMap.contains(animationId)) {
        _currentAnimation = _animationMap[animationId];
    }
}

void spic::Animator::Render(spic::Transform transform) {
    if (!_isPlaying || _currentAnimation == nullptr) return;
    _currentAnimation->Draw(transform);
}

void spic::Animator::Update() {
    if (!_isPlaying || _currentAnimation == nullptr) return;
    _currentAnimation->Update();
    if (_currentAnimation->GetCurrentFrame() == _currentAnimation->GetFrameCount() && !_isLooping) {
        _isPlaying = false;
    }
}

void spic::Animator::Play(bool looping) {
    _isPlaying = true;
    _isLooping = looping;
}

void spic::Animator::Stop() {
    _isPlaying = false;
}
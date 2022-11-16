#include "Sprite.hpp"
#include "Point.hpp"
#include "Timer/Timer.hpp"
#include "Render/Window.hpp"

#ifndef PLATFORMER_ENGINE_ANIMATEDSPRITE_HPP
#define PLATFORMER_ENGINE_ANIMATEDSPRITE_HPP

namespace platformer_engine{
    class AnimatedSprite: public spic::Sprite {

    public:
        AnimatedSprite(std::string spriteId, int sortingLayer,
                       int orderInLayer, int spriteWidth, int spriteHeight,
                       int frameCount, int animationSpeed, int spriteRow, platformer_engine::SPIC_RendererFlip flip = platformer_engine::FLIP_NONE, spic::Color color = spic::Color::Transparent());

        void Update();
        void Draw(spic::Point location);
        void ResetCurrentFrame();

    private:
        int _currentFrame;
        int _frameCount;
        int _animationSpeed;
        int _spriteRow;
    };
}

#endif //PLATFORMER_ENGINE_ANIMATEDSPRITE_HPP

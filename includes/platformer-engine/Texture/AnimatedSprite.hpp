#include "Sprite.hpp"
#include "Point.hpp"
#include "Timer/Timer.hpp"
#include "Render/Window.hpp"
#include "Transform.hpp"
#include <boost/serialization/access.hpp>

#ifndef PLATFORMER_ENGINE_ANIMATEDSPRITE_HPP
#define PLATFORMER_ENGINE_ANIMATEDSPRITE_HPP


namespace platformer_engine {
    /**
     * @brief AnimatedSprite class which is used to animate sprites
     */
    class AnimatedSprite : public spic::Sprite {
        static const int ANIMATION_SPEED = 100;
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<spic::Sprite, AnimatedSprite>(*this);
            boost::serialization::void_cast_register<AnimatedSprite, spic::Sprite>();
            ar & _currentFrame;
            ar & _frameCount;
            ar & _animationSpeed;
            ar & _spriteRow;
        }

        AnimatedSprite();

        AnimatedSprite(const AnimatedSprite &other) = default;

        AnimatedSprite(AnimatedSprite &&other) = default;

        AnimatedSprite &operator=(AnimatedSprite &&other) = default;

        auto operator=(const AnimatedSprite &other) -> AnimatedSprite & = default;

        ~AnimatedSprite() = default;

        /**
         * @brief Animated sprite constructor
         * @param spriteId sprite ID to use
         * @param spriteWidth width of the sprite
         * @param spriteHeight height of the sprite
         * @param sortingLayer sorting layer
         * @param orderInLayer order in layer
         * @param frameCount amount of frames in animation
         * @param animationSpeed speed of the animation
         * @param spriteRow row where the animation is located in the sprite
         * @param flip If the sprite should be flipped and in which direction
         * @param color background color
         */
        AnimatedSprite(std::string spriteId, int spriteWidth, int spriteHeight, int frameCount, int sortingLayer = 1,
                       int orderInLayer = 1,
                       int animationSpeed = ANIMATION_SPEED, int spriteRow = 1,
                       platformer_engine::SPIC_RendererFlip flip = platformer_engine::FLIP_NONE,
                       spic::Color color = spic::Color::Transparent(), double spriteScale = 1.0);

        /**
         * @brief Update frame count
         */
        void Update();

        /**
         * @brief Draw the animation on the window
         * @param location Location where to draw the animation
         */
        void Draw(spic::Transform transform);

        /**
         * @brief Set current frame to 0
         */
        void ResetCurrentFrame();

        /**
         * @brief Get the current frame
         * @return int current frame
         */
        [[nodiscard]] inline auto GetCurrentFrame() const -> int { return _currentFrame; };

        /**
         * @brief Get the animation frame count
         * @return int animation frame count
         */
        [[nodiscard]] inline auto GetFrameCount() const -> int { return _frameCount; };


    private:
        int _currentFrame{};

        int _frameCount{};

        int _animationSpeed{};

        int _spriteRow{};
    };
}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_ANIMATEDSPRITE_HPP

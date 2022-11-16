#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.hpp"
#include "Sprite.hpp"
#include "Texture/AnimatedSprite.hpp"
#include "Point.hpp"

namespace spic {

    /**
     * @brief A component which can play animated sequences of sprites.
     */
    class Animator : public Component {
        public:
            Animator(const std::shared_ptr<platformer_engine::AnimatedSprite>& animatedSprite, bool isPlaying = true, bool isLooping = true);
            /**
             * @brief Start playing the image sequence.
             * @param looping If true, will automatically start again when done.
             * @spicapi
             */
            void Play(bool looping);

            /**
             * @brief Stop playing the image sequence. Whatever sprite was displayed
             *        last will remain shown.
             * @spicapi
             */
            void Stop();

            /**
             * @brief Add an animation to the Animator
             * @param animatedSprite animatedSprite to add
             */
            void AddAnimation(const std::shared_ptr<platformer_engine::AnimatedSprite>& animatedSprite);
            /**
             * @brief Set the current animation
             * @param animatedSprite animatedSprite to set
             */
            void SetActiveAnimation(const std::string& animationId);
            /**
             * @brief Render the current animated sprite
             */
            void Render(spic::Point location);
            /**
             * @brief Update the animated sprite (current frame)
             */
            void Update();

        private:
            /**
             * @brief frames per second (playing speed)
             * @spicapi
             */
            [[maybe_unused]] int _fps;

            /**
             * @brief Map with animation ID and animated sprite shared_ptr
             */
            std::map<std::string, std::shared_ptr<platformer_engine::AnimatedSprite>> _animationMap;
            /**
             * @brief Current active animation
             */
            std::shared_ptr<platformer_engine::AnimatedSprite> _currentAnimation;
            /**
             * @brief boolean to toggle if an animation is playing
             */
            bool _isPlaying;
            /**
             * @brief boolean to toggle if an animation is looping
             */
            bool _isLooping;
    };

}

#endif // ANIMATOR_H_

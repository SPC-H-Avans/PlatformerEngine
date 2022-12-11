#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.hpp"
#include "Sprite.hpp"
#include "Texture/AnimatedSprite.hpp"
#include "Point.hpp"
#include "Transform.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>

namespace spic {

    /**
     * @brief A component which can play animated sequences of sprites.
     */
    class Animator : public Component {
    public:

        Animator();

        ~Animator() = default;

        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<Component, Animator>(*this);
            boost::serialization::void_cast_register<Animator, Component>();
            ar & _animationMap;
            ar & _currentAnimation;
            ar & _isPlaying;
            ar & _isLooping;
        }

        Animator(const platformer_engine::AnimatedSprite &animatedSprite, bool isPlaying = true,
                 bool isLooping = true);

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
        void AddAnimation(const platformer_engine::AnimatedSprite &animatedSprite);

        /**
         * @brief Set the current animation
         * @param animatedSprite animatedSprite to set
         */
        void SetActiveAnimation(const std::string &animationId);

        /**
         * @brief Render the current animated sprite
         * @param Transform transform to use
         */
        void Render(spic::Transform transform);

        /**
         * @brief Update the animated sprite (current frame)
         */
        void Update(double deltaTime);

        auto inline
        GetLoadedAnimations() -> std::map<std::string, std::shared_ptr<platformer_engine::AnimatedSprite>> { return _animationMap; };

    private:
        /**
         * @brief Map with animation ID and animated sprite shared_ptr
         */
        std::map<std::string, std::shared_ptr<platformer_engine::AnimatedSprite>> _animationMap;
        /**
         * @brief Current active animation
         */
        std::shared_ptr<platformer_engine::AnimatedSprite> _currentAnimation{nullptr};
        /**
         * @brief boolean to toggle if an animation is playing
         */
        bool _isPlaying = true;
        /**
         * @brief boolean to toggle if an animation is looping
         */
        bool _isLooping = true;
    };

}  // namespace spic

#endif // ANIMATOR_H_

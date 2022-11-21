#ifndef PLATFORMER_ENGINE_BUILDER_HPP
#define PLATFORMER_ENGINE_BUILDER_HPP

#include "Texture/AnimatedSprite.hpp"

/**
 * @brief Base class for GameObjectBuilders.
*/
class ObjectBuilder {
public:
    /**
     * @brief Adds an AudioSource component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddAudioSource() -> ObjectBuilder & = 0;

    /**
     * @brief Adds an Animator component to the current GameObject being build.
     * @param animatedSprite the AnimatedSprite to be used by the Animator.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddAnimator(std::shared_ptr<platformer_engine::AnimatedSprite> animatedSprite) -> ObjectBuilder & = 0;

    /**
     * @brief Adds an Animator component to the current GameObject being build.
     * @param animatedSprite List of AnimatedSprite to be used by the Animator.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto
    AddAnimator(std::vector<std::shared_ptr<platformer_engine::AnimatedSprite>> animatedSprite) -> ObjectBuilder & = 0;

    /**
     * @brief Adds a BehaviourScript component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddBehaviourScript() -> ObjectBuilder & = 0;

    /**
     * @brief Adds a Collider component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddCollider() -> ObjectBuilder & = 0;

    /**
     * @brief Adds a RigidBody component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddRigidBody() -> ObjectBuilder & = 0;

    /**
     * @brief Adds a Sprite component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddSprite(const std::shared_ptr<spic::Sprite> &sprite) -> ObjectBuilder & = 0;
};

#endif //PLATFORMER_ENGINE_BUILDER_HPP

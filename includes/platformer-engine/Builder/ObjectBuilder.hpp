#ifndef PLATFORMER_ENGINE_BUILDER_HPP
#define PLATFORMER_ENGINE_BUILDER_HPP

#include "Texture/AnimatedSprite.hpp"
#include "BehaviourScript.hpp"
#include "RigidBody.hpp"
#include "AudioSource.hpp"

/**
 * @brief Base class for GameObjectBuilders.
*/
class ObjectBuilder {
public:
    /**
     * @brief Adds an AudioSource component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddAudioSource(const spic::AudioSource audioSource) -> ObjectBuilder & = 0;

    /**
     * @brief Adds an Animator component to the current GameObject being build.
     * @param animatedSprite the AnimatedSprite to be used by the Animator.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddAnimator(platformer_engine::AnimatedSprite &animatedSprite) -> ObjectBuilder & = 0;

    /**
     * @brief Adds an Animator component to the current GameObject being build.
     * @param animatedSprite List of AnimatedSprite to be used by the Animator.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto
    AddAnimator(std::vector<platformer_engine::AnimatedSprite> &animatedSprite) -> ObjectBuilder & = 0;

    /**
     * @brief Adds a BehaviourScript component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddBehaviourScript(const BehaviourScript &script) -> ObjectBuilder & = 0;

    /**
     * @brief Adds a Collider component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddCollider(const spic::Collider collider) -> ObjectBuilder & = 0;

    /**
     * @brief Adds a RigidBody component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddRigidBody(const spic::RigidBody rigidBody) -> ObjectBuilder & = 0;

    /**
     * @brief Adds a Sprite component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddSprite(const spic::Sprite &sprite) -> ObjectBuilder & = 0;

    /**
     * @brief Adds a Transform component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto AddTransform(const spic::Transform &transform) -> ObjectBuilder & = 0;

    /**
     * @brief Sets the owner id of the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual auto SetOwnerId(int ownerId) -> ObjectBuilder & = 0;
};

#endif //PLATFORMER_ENGINE_BUILDER_HPP

#ifndef PLATFORMER_ENGINE_BUILDER_HPP
#define PLATFORMER_ENGINE_BUILDER_HPP

/**
 * @brief Base class for GameObjectBuilders.
*/
class ObjectBuilder {
public:
    /**
     * @brief Adds an AudioSource component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual ObjectBuilder& AddAudioSource() = 0;

    /**
     * @brief Adds an Animator component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual ObjectBuilder& AddAnimator() = 0;

    /**
     * @brief Adds a BehaviourScript component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual ObjectBuilder& AddBehaviourScript() = 0;

    /**
     * @brief Adds a Collider component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual ObjectBuilder& AddCollider() = 0;

    /**
     * @brief Adds a RigidBody component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual ObjectBuilder& AddRigidBody() = 0;

    /**
     * @brief Adds a Sprite component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    virtual ObjectBuilder& AddSprite() = 0;
};

#endif //PLATFORMER_ENGINE_BUILDER_HPP

#ifndef PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP
#define PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP

#include "GameObject.hpp"
#include "ObjectBuilder.hpp"
#include "Animator.hpp"
#include "Texture/AnimatedSprite.hpp"

using namespace spic;

/**
 * @brief Implementation of ObjectBuilder to create gameobjects with ease.
 */
class GameObjectBuilder : ObjectBuilder {
public:
    /**
     * @brief Constructor
     * @param name the name being used to instantiate the new GameObject
     */
    GameObjectBuilder(const std::string &name);

    /**
     * @brief Sets a new instance of GameObject on the gameObject variable using the given name;
     * @param name the name being used to instantiate the new GameObject
     * @return shared pointer to GameObject. (Shared with static instance list)
     */
    void Reset(const std::string &name);

    /**
     * @brief Returns the GameObject to the creator.
     * @return shared pointer to GameObject. (Shared with static instance list)
     */
    auto GetGameObject() -> std::shared_ptr<GameObject>;

    /**
     * @brief Adds an Animator component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    auto AddAnimator(std::shared_ptr<platformer_engine::AnimatedSprite> animatedSprite) -> GameObjectBuilder & override;

    /**
     * @brief Adds an AudioSource component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    auto AddAudioSource() -> GameObjectBuilder & override;

    /**
     * @brief Adds an Animator component to the current GameObject being build.
     * @param animatedSprite List of AnimatedSprite to be used by the Animator.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    auto AddAnimator(
            std::vector<std::shared_ptr<platformer_engine::AnimatedSprite>> animatedSprite) -> GameObjectBuilder & override;

    /**
     * @brief Adds a BehaviourScript component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    auto AddBehaviourScript() -> GameObjectBuilder & override;

    /**
     * @brief Adds a Collider component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    auto AddCollider() -> GameObjectBuilder & override;

    /**
     * @brief Adds a RigidBody component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    auto AddRigidBody() -> GameObjectBuilder & override;

    /**
     * @brief Adds a Sprite component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    auto AddSprite(const std::shared_ptr<spic::Sprite> &sprite) -> GameObjectBuilder & override;

private:
    //Shares ptr with GameObject static instace list
    std::shared_ptr<GameObject> _gameObject;
};

#endif //PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP

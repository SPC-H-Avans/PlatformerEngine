#ifndef PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP
#define PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP

#include "GameObject.hpp"
#include "ObjectBuilder.hpp"
using namespace spic;

/**
 * @brief Implementation of ObjectBuilder to create GameObjects with ease.
 */
class GameObjectBuilder : ObjectBuilder{
public:
    /**
     * @brief Constructor
     * @param name the name being used to instantiate the new GameObject
     */
    GameObjectBuilder(const std::string& name);

    /**
     * @brief Sets a new instance of GameObject on the GameObject variable using the given name;
     * @param name the name being used to instantiate the new GameObject
     * @return shared pointer to GameObject. (Shared with static instance list)
     */
    void Reset(const std::string& name);

    /**
     * @brief Returns the GameObject to the creator.
     * @return shared pointer to GameObject. (Shared with static instance list)
     */
    std::shared_ptr<GameObject> GetGameObject();

    /**
     * @brief Adds an AudioSource component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    GameObjectBuilder& AddAudioSource() override;

    /**
     * @brief Adds an Animator component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    GameObjectBuilder& AddAnimator() override;

    /**
     * @brief Adds a BehaviourScript component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    GameObjectBuilder& AddBehaviourScript() override;

    /**
     * @brief Adds a Collider component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    GameObjectBuilder& AddCollider() override;

    /**
     * @brief Adds a RigidBody component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    GameObjectBuilder& AddRigidBody() override;

    /**
     * @brief Adds a Sprite component to the current GameObject being build.
     * @return reference to ObjectBuilder, allows method chaining.
     */
    GameObjectBuilder& AddSprite() override;
private:
    //Shares ptr with GameObject static instace list
    std::shared_ptr<GameObject> _gameObject;
};

#endif //PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP

#ifndef PLATFORMER_ENGINE_GAMEOBJECTDIRECTOR_HPP
#define PLATFORMER_ENGINE_GAMEOBJECTDIRECTOR_HPP

#include "Builder/GameObjectBuilder.hpp"

/**
 * @brief The GameObjectDirector can be used to easily create specialised GameObjects
 */
class GameObjectDirector {
public:
    /**
     * @brief Constructor
     */
    GameObjectDirector() = default;

    /**
     * @brief Create a tile (collidable) and add it to the scene
     * @param sprite the sprite to use
     * @param transform the transform to use
     * @param colliderWidth the width of the collider
     * @param colliderHeight the height of the collider
     * @return The created GameObject
     */
    static auto CreateTile(
            const std::shared_ptr<Sprite>& sprite,
            Transform transform,
            int colliderWidth,
            int colliderHeight
    ) -> std::shared_ptr<GameObject>;

    /**
     * @brief Create a background object (not collidable) and add it to the scene
     * @param sprite the sprite to use
     * @param transform the transform to use
     * @return The created GameObject
     */
    static auto CreateBackgroundObject(
            const std::shared_ptr<Sprite>& sprite,
            Transform transform
    ) -> std::shared_ptr<GameObject>;

    /**
     * @brief Create a background object (not collidable) and add it to the scene
     * @param sprite the sprite to use
     * @param transform the transform to use
     * @param colliderWidth the width of the collider
     * @param colliderHeight the height of the collider
     * @return The created GameObject
     */
    static auto CreatePlayer(
            const std::shared_ptr<platformer_engine::AnimatedSprite>& sprite,
            Transform transform,
            int colliderWidth,
            int colliderHeight
    ) -> std::shared_ptr<GameObject>;
};

#endif //PLATFORMER_ENGINE_GAMEOBJECTDIRECTOR_HPP

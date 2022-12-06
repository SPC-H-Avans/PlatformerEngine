#ifndef PLATFORMER_ENGINE_GAMEOBJECTDIRECTOR_HPP
#define PLATFORMER_ENGINE_GAMEOBJECTDIRECTOR_HPP

#include "Builder/GameObjectBuilder.hpp"
#include "UIObject.hpp"
#include "Text.hpp"
#include "Button.hpp"

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
            const spic::Sprite& sprite,
            Transform transform,
            int colliderWidth,
            int colliderHeight
    ) -> GameObject&;

    /**
     * @brief Create a background object (not collidable) and add it to the scene
     * @param sprite the sprite to use
     * @param transform the transform to use
     * @return The created GameObject
     */
    static auto CreateBackgroundObject(
            const spic::Sprite& sprite,
            Transform transform
    ) -> GameObject&;

    /**
     * @brief Create a background object (not collidable) and add it to the scene
     * @param sprite the sprite to use
     * @param transform the transform to use
     * @param colliderWidth the width of the collider
     * @param colliderHeight the height of the collider
     * @return The created GameObject
     */
    static auto CreatePlayer(
            Transform transform,
            int colliderWidth,
            int colliderHeight,
            std::vector<platformer_engine::AnimatedSprite>& animations,
            const std::vector<std::shared_ptr<BehaviourScript>>& behaviourScripts // must use pointers to store derived classes
    ) -> GameObject&;

    static auto CreateText(Transform transform, const std::string objectId, const std::string text,
                           std::string fontPath, int textWidth, int textHeight,
                           int fontSize, Color textColor) -> Text&;

    static auto CreateButton(Transform transform, const std::string objectId, const spic::Sprite& sprite,
                             int buttonWidth, int buttonHeight) -> Button&;
};

#endif //PLATFORMER_ENGINE_GAMEOBJECTDIRECTOR_HPP

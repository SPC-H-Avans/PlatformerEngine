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
            const spic::Sprite &sprite,
            Transform transform,
            int colliderWidth,
            int colliderHeight
    ) -> GameObject &;

    /**
     * @brief Create a background object (not collidable) and add it to the scene
     * @param sprite the sprite to use
     * @param transform the transform to use
     * @return The created GameObject
     */
    static auto CreateBackgroundObject(
            const spic::Sprite &sprite,
            Transform transform
    ) -> GameObject &;

    /**
     * @brief Create a Player (collidable) and add it to the scene
     * @param transform the transform of the Player
     * @param transform the transform to use
     * @param colliderWidth the width of the collider
     * @param colliderHeight the height of the collider
     * @param animations a vector of AnimatedSprites to use for animations
     * @param behaviourScripts a vector of BehaviourScripts that will apply to the player
     * @return The created GameObject
     */
    static auto CreatePlayer(
            int playerId,
            Transform transform,
            int colliderWidth,
            int colliderHeight,
            std::vector<platformer_engine::AnimatedSprite>& animations,
            const std::vector<std::shared_ptr<BehaviourScript>>& behaviourScripts // must use pointers to store derived classes
    ) -> GameObject&;

    /**
     * @brief Create a background object (not collidable) and add it to the scene
     * @param transform the transform to use
     * @param objectId the identifier of the Button and key of the loaded UIText
     * @param text the shown text
     * @param fontPath the path to the font
     * @param textWidth the width of the text
     * @param textHeight the height of the text
     * @param fontSize the size of the font
     * @param textColor the color of the text
     * @return The created Text
     */
    static auto CreateText(Transform transform, const std::string objectId, const std::string& text,
                           const std::string& fontPath, int textWidth, int textHeight,
                           int fontSize, Color textColor) -> Text&;

    /**
     * @brief Create a background object (not collidable) and add it to the scene
     * @param transform the transform to use
     * @param objectId the identifier of the Button and key of the loaded Sprite
     * @param sprite the sprite to use
     * @param imgPath the path to the sprite image
     * @param buttonWidth the width of the text
     * @param buttonHeight the height of the text
     * @param onClick the function to call when the button is clicked
     * @return The created Button
     */
    static auto CreateButton(Transform transform, const std::string objectId, const spic::Sprite& sprite,
                             const std::string& imgPath, int buttonWidth, int buttonHeight,
                             std::function<void()> onClick) -> Button&;
};

#endif //PLATFORMER_ENGINE_GAMEOBJECTDIRECTOR_HPP

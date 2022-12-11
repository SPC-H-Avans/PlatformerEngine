#ifndef PLATFORMER_ENGINE_RENDERSYSTEM_HPP
#define PLATFORMER_ENGINE_RENDERSYSTEM_HPP
#include "GameObject.hpp"
#include "Animator.hpp"
/**
 * @brief System that updates the animation of the AnimatedSprite component.
 */
class RenderSystem {

public:
    /**
     * @brief Update all sprites, currently only used to update animated sprites
     */
    static void Update(double deltaTime);
    /**
     * @brief Render all objects on the screen
     */
    static void Render();
};
#endif //PLATFORMER_ENGINE_RENDERSYSTEM_HPP

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

    static auto CreateTile(
            const std::shared_ptr<Sprite>& sprite,
            Transform transform
            ) -> std::shared_ptr<GameObject>;
//    auto CreatePlayer() -> std::shared_ptr<GameObject>;
private:
//    GameObjectBuilder _builder;
};

#endif //PLATFORMER_ENGINE_GAMEOBJECTDIRECTOR_HPP

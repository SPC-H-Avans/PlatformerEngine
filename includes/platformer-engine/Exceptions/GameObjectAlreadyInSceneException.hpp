//
// Created by jhpar on 14-11-2022.
//

#ifndef PLATFORMER_ENGINE_GAMEOBJECTALREADYINSCENEEXCEPTION_CPP_H
#define PLATFORMER_ENGINE_GAMEOBJECTALREADYINSCENEEXCEPTION_CPP_H

#include <stdexcept>

namespace spic {
    class GameObjectAlreadyInSceneException : public std::logic_error
    {
    public:
        GameObjectAlreadyInSceneException (const std::string& gameObjectName) : std::logic_error{"The Game Object with name: " + gameObjectName + " is already added to this scene!"} {}
    };
}
#endif //PLATFORMER_ENGINE_GAMEOBJECTALREADYINSCENEEXCEPTION_CPP_H

//
// Created by Niels on 7-11-2022.
//

#ifndef PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP
#define PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP

#include "GameObject.hpp"
#include "ObjectBuilder.hpp"
using namespace spic;

class GameObjectBuilder : ObjectBuilder{
public:
    GameObjectBuilder(const std::string& name);
    void Reset(const std::string& name);

private:
    std::unique_ptr<GameObject> gameObject;
};

#endif //PLATFORMER_ENGINE_GAMEOBJECTBUILDER_HPP

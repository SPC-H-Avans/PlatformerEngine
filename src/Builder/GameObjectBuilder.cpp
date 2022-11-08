//
// Created by Niels on 7-11-2022.
//
#include "Builder/GameObjectBuilder.hpp"

GameObjectBuilder::GameObjectBuilder(const std::string &name) : gameObject(std::make_unique<GameObject>(name)) {}

void GameObjectBuilder::Reset(const std::string &name) {
    this->gameObject = std::make_unique<GameObject>(name);
}

std::shared_ptr<GameObject> GameObjectBuilder::GetGameObject() {
    return gameObject;
}

//Return *this in every component method to allow chaining

ObjectBuilder& GameObjectBuilder::AddAudio() {
    //Add audiosource to gameobject
    return *this;
}
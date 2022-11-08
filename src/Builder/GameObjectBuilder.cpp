//
// Created by Niels on 7-11-2022.
//
#include "Builder/GameObjectBuilder.hpp"

GameObjectBuilder::GameObjectBuilder(const std::string &name) : gameObject(std::make_shared<GameObject>(name)), copyCounter(0), originalName(name) {}

//If reset with exisitng name append number to it
void GameObjectBuilder::Reset(const std::string &name) {
    gameObject = std::make_shared<GameObject>(name);
}

std::shared_ptr<GameObject> GameObjectBuilder::GetGameObject() {
    auto name = gameObject->GetName();
    Reset(name);
    return GameObject::Find(name);
}

//Return *this in every component method to allow chaining
ObjectBuilder& GameObjectBuilder::AddAudioSource() {
    //TODO Add audiosource to gameobject
    return *this;
}

ObjectBuilder& GameObjectBuilder::AddAnimator() {
    //TODO add animotor to gameobject
    return *this;
}

ObjectBuilder& GameObjectBuilder::AddBehaviourScript() {
    //TODO add behaviourscript to gameobject
    return *this;
}

ObjectBuilder &GameObjectBuilder::AddCollider() {
    //TODO add collider to gameobject
    //DO WE NEED SEPERATE FUNCTIONS FOR DIFFERENT COLLIDERS?
    return *this;
}

ObjectBuilder &GameObjectBuilder::AddRigidBody() {
    //TODO add rigidbody to gameobject
    return *this;
}

ObjectBuilder &GameObjectBuilder::AddSprite() {
    //TODO add sprite to gameobject
    return *this;
}
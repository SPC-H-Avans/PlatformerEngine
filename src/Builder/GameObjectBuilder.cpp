#include "Builder/GameObjectBuilder.hpp"
#include <stdexcept>

GameObjectBuilder::GameObjectBuilder(const std::string &name) : _gameObject(std::make_shared<GameObject>(name)) {}

//If reset with existing name append number to it
void GameObjectBuilder::Reset(const std::string &name) {
    _gameObject = std::make_shared<GameObject>(name);
}

std::shared_ptr<GameObject> GameObjectBuilder::GetGameObject() {
    auto name = _gameObject->GetName();
    Reset(name);
    return GameObject::Find(name);
}

//Return *this in every component method to allow chaining
GameObjectBuilder& GameObjectBuilder::AddAudioSource() {
    //TODO Add audiosource to gameobject
    throw std::logic_error("Function not implemented");
    return *this;
}

GameObjectBuilder& GameObjectBuilder::AddAnimator() {
    //TODO add animotor to gameobject
    throw std::logic_error("Function not implemented");
    return *this;
}

GameObjectBuilder& GameObjectBuilder::AddBehaviourScript() {
    //TODO add behaviourscript to gameobject
    throw std::logic_error("Function not implemented");
    return *this;
}

GameObjectBuilder &GameObjectBuilder::AddCollider() {
    //TODO add collider to gameobject
    //DO WE NEED SEPERATE FUNCTIONS FOR DIFFERENT COLLIDERS?
    throw std::logic_error("Function not implemented");
    return *this;
}

GameObjectBuilder &GameObjectBuilder::AddRigidBody() {
    //TODO add rigidbody to gameobject
    throw std::logic_error("Function not implemented");
    return *this;
}

GameObjectBuilder &GameObjectBuilder::AddSprite() {
    //TODO add sprite to gameobject
    throw std::logic_error("Function not implemented");
    return *this;
}
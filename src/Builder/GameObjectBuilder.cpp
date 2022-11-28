#include "Builder/GameObjectBuilder.hpp"
#include <stdexcept>

GameObjectBuilder::GameObjectBuilder(const std::string &name) : _gameObject(std::make_shared<GameObject>(name)) {}

//If reset with existing name append number to it
void GameObjectBuilder::Reset(const std::string &name) {
    _gameObject = std::make_shared<GameObject>(name);
}

auto GameObjectBuilder::GetGameObject() -> std::shared_ptr<GameObject> {
    auto name = _gameObject->GetName();
    Reset(name);
    return GameObject::Find(name);
}

//Return *this in every component method to allow chaining
auto GameObjectBuilder::AddAudioSource() -> GameObjectBuilder & {
    //TODO Add audiosource to gameobject
    throw std::logic_error("Function not implemented");
    return *this;
}

auto
GameObjectBuilder::AddAnimator(std::shared_ptr<platformer_engine::AnimatedSprite> animatedSprite) -> GameObjectBuilder & {
    std::shared_ptr<Animator> animator = std::make_shared<Animator>(animatedSprite);
    _gameObject->AddComponent<Animator>(animator);
    return *this;
}

auto
GameObjectBuilder::AddAnimator(
        std::vector<std::shared_ptr<platformer_engine::AnimatedSprite>> animatedSprite) -> GameObjectBuilder & {
    if (animatedSprite.empty()) {
        throw std::invalid_argument("animatedSprite is empty");
    }
    std::shared_ptr<Animator> animator = std::make_shared<Animator>(animatedSprite.back());
    for (const auto &item: animatedSprite) {
        animator->AddAnimation(item);
    }
    _gameObject->AddComponent<Animator>(animator);
    return *this;
}

auto GameObjectBuilder::AddBehaviourScript() -> GameObjectBuilder & {
    //TODO add behaviourscript to gameobject
    throw std::logic_error("Function not implemented");
    return *this;
}

auto GameObjectBuilder::AddCollider() -> GameObjectBuilder & {
    //TODO add collider to gameobject
    //DO WE NEED SEPERATE FUNCTIONS FOR DIFFERENT COLLIDERS?
    throw std::logic_error("Function not implemented");
    return *this;
}

auto GameObjectBuilder::AddRigidBody() -> GameObjectBuilder & {
    //TODO add rigidbody to gameobject
    throw std::logic_error("Function not implemented");
    return *this;
}

auto GameObjectBuilder::AddSprite(const std::shared_ptr<spic::Sprite> &sprite) -> GameObjectBuilder & {
    _gameObject->AddComponent<Sprite>(sprite);
    return *this;
}
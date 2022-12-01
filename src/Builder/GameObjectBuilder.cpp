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

auto GameObjectBuilder::AddAnimator(platformer_engine::AnimatedSprite &animatedSprite) -> GameObjectBuilder & {
    auto sharedSprite = platformer_engine::AnimatedSprite(animatedSprite);
    auto animator = std::make_shared<Animator>(sharedSprite);
    _gameObject->AddComponent<Animator>(animator);
    return *this;
}

auto GameObjectBuilder::AddAnimator(std::vector<platformer_engine::AnimatedSprite> &animatedSprite) -> GameObjectBuilder & {
    if (animatedSprite.empty()) {
        throw std::invalid_argument("animatedSprite is empty");
    }
    auto animator = std::make_shared<Animator>(
            platformer_engine::AnimatedSprite(animatedSprite.back()));
    for (const auto &item: animatedSprite) {
        animator->AddAnimation(platformer_engine::AnimatedSprite(item));
    }
    _gameObject->AddComponent<Animator>(animator);
    return *this;
}

auto GameObjectBuilder::AddBehaviourScript(const BehaviourScript &script) -> GameObjectBuilder & {
    _gameObject->AddComponent<BehaviourScript>(std::make_shared<BehaviourScript>(script));
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

auto GameObjectBuilder::AddSprite(const spic::Sprite &sprite) -> GameObjectBuilder & {
    _gameObject->AddComponent<Sprite>(std::make_shared<Sprite>(sprite));
    return *this;
}
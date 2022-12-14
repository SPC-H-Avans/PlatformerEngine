#include "Builder/GameObjectBuilder.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include <stdexcept>

GameObjectBuilder::GameObjectBuilder(const std::string &name) : _gameObject(std::make_shared<GameObject>(name)) {}

GameObjectBuilder::GameObjectBuilder(const std::string &name, const std::string &tag) : _gameObject(std::make_shared<GameObject>(name, tag)) {}

//If reset with existing name append number to it
void GameObjectBuilder::Reset(const std::string &name) {
    _gameObject = std::make_shared<GameObject>(name);
}

void GameObjectBuilder::Reset(const std::string &name, const std::string &tag) {
    _gameObject = std::make_shared<GameObject>(name, tag);
}

auto GameObjectBuilder::GetGameObject() -> std::shared_ptr<GameObject> {
    auto name = _gameObject->GetName();
    Reset(name);
    return GameObject::Find(name);
}

//Return *this in every component method to allow chaining
auto GameObjectBuilder::AddAudioSource(const spic::AudioSource audioSource) -> GameObjectBuilder & {
    _gameObject->AddComponent<AudioSource>(std::make_shared<AudioSource>(audioSource));
    return *this;
}

auto GameObjectBuilder::AddAnimator(platformer_engine::AnimatedSprite &animatedSprite) -> GameObjectBuilder & {
    auto sharedSprite = platformer_engine::AnimatedSprite(animatedSprite);
    auto animator = std::make_shared<Animator>(sharedSprite);
    _gameObject->AddComponent<Animator>(animator);
    return *this;
}

auto
GameObjectBuilder::AddAnimator(std::vector<platformer_engine::AnimatedSprite> &animatedSprite) -> GameObjectBuilder & {
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

auto GameObjectBuilder::AddCollider(const spic::Collider collider) -> GameObjectBuilder & {
    _gameObject->AddComponent<BoxCollider>(std::make_shared<Collider>(collider));
    return *this;
}

auto GameObjectBuilder::AddRigidBody(const spic::RigidBody rigidBody) -> GameObjectBuilder & {
    _gameObject->AddComponent<RigidBody>(std::make_shared<RigidBody>(rigidBody));
    return *this;
}

auto GameObjectBuilder::AddSprite(const spic::Sprite &sprite) -> GameObjectBuilder & {
    _gameObject->AddComponent<Sprite>(std::make_shared<Sprite>(sprite));
    return *this;
}

auto GameObjectBuilder::AddTransform(const spic::Transform &transform) -> GameObjectBuilder & {
    _gameObject->SetTransform(transform);
    return *this;
}

auto GameObjectBuilder::SetOwnerId(int ownerId) -> GameObjectBuilder & {
    _gameObject->SetOwnerId(ownerId);
    return *this;
}

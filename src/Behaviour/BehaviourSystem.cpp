#include "Behaviour/BehaviourSystem.hpp"
#include "BehaviourScript.hpp"
#include "GameObject.hpp"

void BehaviourSystem::Start() {
    auto gameObjects = GameObject::FindObjectsOfType<GameObject>();
    for(auto& gameObject : gameObjects) {
        auto scripts = gameObject->GetComponents<BehaviourScript>();
        for(auto& scriptComponent : scripts) {
            auto script = std::dynamic_pointer_cast<spic::BehaviourScript>(scriptComponent);
            if (script != nullptr) script->OnStart();
        }
    }
}

void BehaviourSystem::Update() {
    auto gameObjects = GameObject::FindObjectsOfType<GameObject>();
    for(auto& gameObject : gameObjects) {
        auto scripts = gameObject->GetComponents<BehaviourScript>();
        for(auto& scriptComponent : scripts) {
            auto script = std::dynamic_pointer_cast<spic::BehaviourScript>(scriptComponent);
            if (script != nullptr) script->OnUpdate();
        }
    }
}
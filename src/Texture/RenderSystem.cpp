#include "Texture/RenderSystem.hpp"
#include "Engine/Engine.hpp"

void RenderSystem::Update() {
    auto allGameObjects = spic::GameObject::FindObjectsOfType<spic::GameObject>();
    for (const auto &item: allGameObjects) {
        if(item == nullptr) continue;
        auto animatorComponent = item->GetComponent<spic::Animator>();
        if (animatorComponent == nullptr) continue;
        auto animator = std::static_pointer_cast<spic::Animator>(animatorComponent);
        animator->Update();
    }
}

void RenderSystem::Render() {
    //First render the scene, then gameObjects
    auto &scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    scene.RenderScene();
}

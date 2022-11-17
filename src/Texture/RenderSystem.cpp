#include "Texture/RenderSystem.hpp"

void RenderSystem::Update() {
  auto allGameObjects = spic::GameObject::FindObjectsOfType<spic::GameObject>();
    for (const auto &item: allGameObjects){
       auto animatorComponent = item->GetComponent<spic::Animator>();
       if(animatorComponent == nullptr) continue;
       auto animator = std::static_pointer_cast<spic::Animator>(animatorComponent);
       animator->Update();
    }
}

void RenderSystem::Render() {
    auto allGameObjects = spic::GameObject::FindObjectsOfType<spic::GameObject>();
    for (const auto &item: allGameObjects){
        auto animatorComponent = item->GetComponent<spic::Animator>();
        if(animatorComponent == nullptr) continue;
        auto animator = std::static_pointer_cast<spic::Animator>(animatorComponent);
        animator->Render(item->GetTransform());
    }
}

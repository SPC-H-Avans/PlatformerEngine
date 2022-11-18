#include "Builder/SceneBuilder.hpp"

platformer_engine::SceneBuilder::SceneBuilder() {
    _scene = std::make_unique<spic::Scene>();
}

platformer_engine::SceneBuilder &platformer_engine::SceneBuilder::AddGameObject(const std::shared_ptr<spic::GameObject>& gameObject) {
    _scene->AddObject(gameObject);
    return *this;
}

platformer_engine::SceneBuilder &platformer_engine::SceneBuilder::AddGameObjects(const std::vector<std::shared_ptr<spic::GameObject>>& gameObjects) {
    for (const auto &item: gameObjects){
        _scene->AddObject(item);
    }
    return *this;
}

platformer_engine::SceneBuilder &platformer_engine::SceneBuilder::AddCamera(const std::shared_ptr<spic::Camera>& camera) {
    _scene->AddCamera(camera);
    return *this;
}

std::unique_ptr<spic::Scene> platformer_engine::SceneBuilder::GetScene() {
    return std::move(_scene);
}
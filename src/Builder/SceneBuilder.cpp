#include "Builder/SceneBuilder.hpp"

SceneBuilder::SceneBuilder() {
    _scene = std::make_unique<spic::Scene>();
}

SceneBuilder &SceneBuilder::AddGameObject(const std::shared_ptr<spic::GameObject>& gameObject) {
    _scene->AddObject(gameObject);
    return *this;
}

SceneBuilder &SceneBuilder::AddGameObjects(const std::vector<std::shared_ptr<spic::GameObject>>& gameObjects) {
    for (const auto &item: gameObjects){
        _scene->AddObject(item);
    }
    return *this;
}

SceneBuilder &SceneBuilder::AddCamera(const std::shared_ptr<spic::Camera>& camera) {
    _scene->AddCamera(camera);
    return *this;
}

std::unique_ptr<spic::Scene> SceneBuilder::GetScene() {
    return std::move(_scene);
}
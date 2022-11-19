#include "Builder/SceneBuilder.hpp"

platformer_engine::SceneBuilder::SceneBuilder() {
    _scene = std::make_unique<spic::Scene>();
}

auto platformer_engine::SceneBuilder::AddGameObject(
        const std::shared_ptr<spic::GameObject> &gameObject) -> platformer_engine::SceneBuilder & {
    _scene->AddObject(gameObject);
    return *this;
}

auto platformer_engine::SceneBuilder::AddGameObjects(
        const std::vector<std::shared_ptr<spic::GameObject>> &gameObjects) -> platformer_engine::SceneBuilder & {
    for (const auto &item: gameObjects) {
        _scene->AddObject(item);
    }
    return *this;
}

auto platformer_engine::SceneBuilder::AddCamera(
        const std::shared_ptr<spic::Camera> &camera) -> platformer_engine::SceneBuilder & {
    _scene->AddCamera(camera);
    return *this;
}

auto platformer_engine::SceneBuilder::GetScene() -> std::unique_ptr<spic::Scene> {
    return std::move(_scene);
}
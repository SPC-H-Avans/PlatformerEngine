#include "Builder/SceneBuilder.hpp"

platformer_engine::SceneBuilder::SceneBuilder(const std::string &name) {
    _scene = spic::Scene(name);
}

auto platformer_engine::SceneBuilder::AddGameObject(
        const spic::GameObject& gameObject) -> platformer_engine::SceneBuilder & {
    _scene.AddObject(gameObject);
    return *this;
}

auto platformer_engine::SceneBuilder::AddGameObjects(
        const std::vector<std::shared_ptr<spic::GameObject>>& gameObjects) -> platformer_engine::SceneBuilder & {
    for (const auto &item: gameObjects) {
        _scene.AddObject(*item);
    }
    return *this;
}

auto platformer_engine::SceneBuilder::AddCamera(
        spic::Camera &camera) -> platformer_engine::SceneBuilder & {
    _scene.AddCamera(camera);
    return *this;
}

auto platformer_engine::SceneBuilder::GetScene() -> spic::Scene {
    return _scene;
}
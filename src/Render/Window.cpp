#include "Render/Window.hpp"
#include "LevelParser/LevelParser.hpp"
#include "Input.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    _graphicsFacade = std::make_shared<GraphicsFacade>();
    _graphicsFacade->Init(width, height, title, color);
    TextureManager::GetInstance().Init(_graphicsFacade);
}

void platformer_engine::Window::Clear() {
    _graphicsFacade->Clear();
}

void platformer_engine::Window::Render() {
    _graphicsFacade->Render();
}

void platformer_engine::Window::Quit() {
    _graphicsFacade->Quit();
}

auto platformer_engine::Window::ListenForEvents() -> std::vector<EventsEnum> {
    return spic::Input::ListenForInput();
}

void platformer_engine::Window::SetActiveScene(spic::Scene &scene) {
    //Set all gameobjects active flag to false.
    auto gameObjects = spic::GameObject::FindObjectsOfType<spic::GameObject>();
    for(auto& gameObject : gameObjects) {
        gameObject->Active(false);
    }

    _activeScene = scene;
    //Sets all 'active' objects from this scene as active true
    _activeScene.ResetScene();
}

auto platformer_engine::Window::GetActiveScene() -> spic::Scene & {
    return _activeScene;
}


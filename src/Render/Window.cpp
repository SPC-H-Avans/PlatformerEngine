#include "Render/Window.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    _graphicsFacade.Init(width, height, title, color);
}

void platformer_engine::Window::Render() {
    _graphicsFacade.Clear();

//    Enable once implemented
//    if(_activeScene != nullptr){
//        _activeScene->RenderScene();
//    }

    _graphicsFacade.Render();
}

void platformer_engine::Window::Quit() {
    _graphicsFacade.Quit();
}

auto platformer_engine::Window::ListenForEvents() -> std::vector<EventsEnum> {
   return _inputFacade.ListenForInput();
}

void platformer_engine::Window::SetActiveScene(std::unique_ptr<spic::Scene> scene) {
    _activeScene.swap(scene);
}

std::unique_ptr<spic::Scene> &platformer_engine::Window::GetActiveScene() {
    return _activeScene;
}


#include "Render/Window.hpp"
#include "../../includes/spic-prj-api/Input.hpp"
#include "LevelParser/LevelParser.hpp"

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
   return InputFacade::GetInstance().ListenForInput();
}

void platformer_engine::Window::SetActiveScene(std::unique_ptr<spic::Scene> scene) {
    _activeScene.swap(scene);
}

auto platformer_engine::Window::GetActiveScene() -> std::unique_ptr<spic::Scene> & {
    return _activeScene;
}


#include "Render/Window.hpp"
#include "LevelParser/LevelParser.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    GraphicsFacade::GetInstance().Init(width, height, title, color);
}

void platformer_engine::Window::Clear() {
    GraphicsFacade::GetInstance().Clear();
}

void platformer_engine::Window::Render() {
    GraphicsFacade::GetInstance().Render();
}

void platformer_engine::Window::Quit() {
    GraphicsFacade::GetInstance().Quit();
}

auto platformer_engine::Window::ListenForEvents() -> std::vector<EventsEnum> {
    return InputFacade::GetInstance().ListenForInput();
}

void platformer_engine::Window::SetActiveScene(spic::Scene &scene) {
    _activeScene = scene;
}

auto platformer_engine::Window::GetActiveScene() -> spic::Scene & {
    return _activeScene;
}


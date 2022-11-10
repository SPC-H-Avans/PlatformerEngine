#include "Render/Window.hpp"

platformer_engine::Window::Window(int width, int height, const std::string &title, const spic::Color &color) {
    _graphicsFacade = std::make_shared<GraphicsFacade>();
    _graphicsFacade->Init(width, height, title, color);
    TextureManager::GetInstance().Init(_graphicsFacade);

    //TODO TEMP
    TextureManager::GetInstance().LoadTexture("tree", "D:\\Avans\\Jaar 4\\SPC Project\\assets\\tree.png");
}

void platformer_engine::Window::Render() {
    _graphicsFacade->Clear();

    //TODO iets van gameobjecten plaatsen die gerenderd moeten worden?

    //TODO TEMP
    _graphicsFacade->DrawTexture("tree", 0, 0, 500, 500);

    _graphicsFacade->Render();
}

void platformer_engine::Window::Quit() {
    _graphicsFacade->Quit();
}

auto platformer_engine::Window::ListenForEvents() -> std::vector<EventsEnum> {
   return _inputFacade.ListenForInput();
}


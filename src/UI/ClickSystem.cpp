#include "UI/ClickSystem.hpp"
#include "Engine/Engine.hpp"
#include "Button.hpp"
#include "Input.hpp"
#include "Facade/GraphicsFacade.hpp"

const int MONITOR_WIDTH = 1920;
const int MONITOR_HEIGHT = 1080;

ClickSystem::ClickSystem(bool fullscreen) : _fullscreen(fullscreen) {}

auto ClickSystem::GetRelativeMousePosition() -> std::tuple<int, int> {
    auto mousePosition = spic::Input::MousePosition();
    if (_fullscreen) return std::make_tuple(mousePosition.x, mousePosition.y);

    // commented out because SDL_getMousePos will always return a position that corresponds to a 1920x1080 monitor instead of being relative to the screen size
//    // get screen size, depends on monitor device size
//    auto screenSize = platformer_engine::GraphicsFacade::GetInstance().GetScreenSize();
//    const int screenWidth = std::get<0>(screenSize);
//    const int screenHeight = std::get<1>(screenSize);
    const int screenWidth = MONITOR_WIDTH;
    const int screenHeight = MONITOR_HEIGHT;

    // window size, depends on width and height set in main
    auto window = platformer_engine::Engine::GetInstance().GetWindow();
    const int windowWidth = window.GetWidth();
    const int windowHeight = window.GetHeight();

    // get mouse position
    const int mouseXPos = mousePosition.x / (screenWidth / windowWidth);
    const int mouseYPos = mousePosition.y / (screenHeight / windowHeight);

    return std::make_tuple(mouseXPos, mouseYPos);
}

void ClickSystem::Update(double speedMultiplier) {
    // only check for clicks if the mouse has been clicked this frame
    if (!spic::Input::GetMouseButtonDown(MouseButton::LEFT)) return;

    auto mousePos = GetRelativeMousePosition();
    auto mouseXPos = std::get<0>(mousePos);
    auto mouseYPos = std::get<1>(mousePos);

    auto uiObjects = platformer_engine::Engine::GetInstance().GetActiveScene().GetAllUIObjects();
    for (const auto& obj : uiObjects) {
        // continue if the object is not a button
        auto button = std::dynamic_pointer_cast<Button>(obj);
        if (button == nullptr) continue;

        auto btnTransform = button->GetTransform();

        // top left button position
        auto btnXPos1 = btnTransform.position.x;
        auto btnYPos1 = btnTransform.position.y;

        // bottom right button position
        auto btnXPos2 = btnXPos1 + button->GetWidth();
        auto btnYPos2 = btnYPos1 + button->GetHeight();

        // check if the mouse position overlaps with the button
        if (mouseXPos >= btnXPos1 && mouseXPos <= btnXPos2 &&
            mouseYPos >= btnYPos1 && mouseYPos <= btnYPos2) {
            button->Click();
        }
    }
}

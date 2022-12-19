#include "UI/ClickSystem.hpp"
#include "Engine/Engine.hpp"
#include "Button.hpp"
#include "Input.hpp"
#include "Facade/GraphicsFacade.hpp"

void ClickSystem::Update(double speedMultiplier) {
    // only check for clicks if the mouse has been clicked this frame
    if (!spic::Input::GetMouseButtonDown(MouseButton::LEFT)) return;

    // get screen size, depends on monitor device size
    auto screenSize = platformer_engine::GraphicsFacade::GetInstance().GetScreenSize();
    const int screenWidth = std::get<0>(screenSize);
    const int screenHeight = std::get<1>(screenSize);

    // window size, depends on width and height set in main
    auto window = platformer_engine::Engine::GetInstance().GetWindow();
    const int windowWidth = window.GetWidth();
    const int windowHeight = window.GetHeight();

    // get mouse position
    auto mousePosition = spic::Input::MousePosition();
    const int mouseXPos = mousePosition.x / (screenWidth / windowWidth);
    const int mouseYPos = mousePosition.y / (screenHeight / windowHeight);

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
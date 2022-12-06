#include "UI/ClickSystem.hpp"
#include "Engine/Engine.hpp"
#include "Button.hpp"
#include "Input.hpp"

void ClickSystem::Update() {
    // only check for clicks if the mouse has been clicked this frame
    if (!spic::Input::GetMouseButtonDown(MouseButton::LEFT)) return;

    auto mousePosition = spic::Input::MousePosition();
    auto mouseXPos = mousePosition.x;
    auto mouseYPos = mousePosition.y;

    auto uiObjects = platformer_engine::Engine::GetInstance().GetActiveScene().GetAllUIObjects();
    for (const auto& obj : uiObjects) {
        // continue if the object is not a button
        auto button = std::dynamic_pointer_cast<Button>(obj);
        if (button == nullptr) continue;

        // top left button position
        auto btnTransform = button->GetTransform();
        auto btnXPos1 = btnTransform.position.x * btnTransform.scale;
        auto btnYPos1 = btnTransform.position.y * btnTransform.scale;
        // bottom right button position
        auto btnXPos2 = btnXPos1 + button->GetWidth() * button->GetSprite().GetSpriteScale();
        auto btnYPos2 = btnYPos1 + button->GetHeight() * button->GetSprite().GetSpriteScale();

        // check if the mouse position overlaps with the button
        if (mouseXPos >= btnXPos1 && mouseXPos <= btnXPos2 &&
            mouseYPos >= btnYPos1 && mouseYPos <= btnYPos2) {
            button->Click();
        }
    }
}
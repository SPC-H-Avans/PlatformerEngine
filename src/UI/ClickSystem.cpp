#include "UI/ClickSystem.hpp"
#include "Engine/Engine.hpp"
#include "Button.hpp"

void ClickSystem::Update() {
    auto uiObjects = platformer_engine::Engine::GetInstance().GetActiveScene().GetAllUIObjects();
    for (auto obj : uiObjects) {
//        std::cout << typeid(*obj).name() << std::endl;
        if (static_cast<Button&>(*obj) == static_cast<const GameObject>(nullptr)) {
            std::cout << "1" << std::endl;
        } else {
            std::cout << "2" << std::endl;
        }
    }
}
#include "UI/FPSCounter.hpp"
#include "Director/GameObjectFactory.hpp"
#include "Engine/Engine.hpp"
#include "Behaviour/FPSCounterBehaviour.hpp"

platformer_engine::FPSCounter::FPSCounter(const Transform &transform, std::string &fontPath, const int fontSize,
                                          const Color &fontColor, const int width, const int height,
                                          const KeyCode &key) {
    const std::string textId = "fps" + std::to_string(platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectCount());
    const std::string text = "0";
    auto textObject = GameObjectFactory::CreateText(
            transform,
            textId,
            text,
            fontPath,
            width, height,
            fontSize, fontColor);
    textObject.AddComponent<BehaviourScript>(std::make_shared<platformer_engine::FPSCounterBehaviour>(textId, fontPath, fontSize, fontColor, key));
    _obj = std::make_shared<Text>(textObject);
}
#include "UI/FPSCounter.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "Behaviour/FPSCounterBehaviour.hpp"

platformer_engine::FPSCounter::FPSCounter(const Transform transform, const std::string fontPath, const int fontSize,
                                       const Color fontColor, const int width, const int height) {
    std::string textId = "fps" + std::to_string(platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectCount());
    std::string text = "0";
    auto object = GameObjectDirector::CreateText(
            transform,
            textId,
            text,
            fontPath,
            width, height,
            fontSize, fontColor);
    object.AddComponent<BehaviourScript>(std::make_shared<platformer_engine::FPSCounterBehaviour>(textId, fontPath, fontSize, fontColor));
}

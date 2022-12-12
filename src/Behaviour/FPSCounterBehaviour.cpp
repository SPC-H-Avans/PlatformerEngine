#include "Behaviour/FPSCounterBehaviour.hpp"
#include "Texture/TextureManager.hpp"
#include "Engine/Engine.hpp"
#include "Color.hpp"
#include "Input.hpp"

platformer_engine::FPSCounterBehaviour::FPSCounterBehaviour(const std::string textId, const std::string fontPath, const int fontSize, const Color fontColor, const KeyCode key)
        : _textId(textId), _fontPath(fontPath), _fontSize(fontSize), _fontColor(fontColor), _key(key) {}

void platformer_engine::FPSCounterBehaviour::OnUpdate() {
    if (spic::Input::GetKeyDown(_key)) {
        _active = !_active;
        // if counter turned off, update the text to show nothing to "hide" it
        if (!_active) platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(_textId, _fontPath, " ", _fontSize, _fontColor);
        if (_active) _lastFPS = -1;
    }

    if (!_active) return;

    auto fps = platformer_engine::Engine::GetInstance().GetFPS();

    if (fps != _lastFPS) {
        _lastFPS = fps;
        std::string fpsText = std::to_string(fps);
        platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(_textId, _fontPath, fpsText, _fontSize, _fontColor);
    }
}
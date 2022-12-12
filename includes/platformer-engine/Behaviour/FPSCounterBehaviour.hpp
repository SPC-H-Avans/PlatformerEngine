#ifndef PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Color.hpp"

namespace platformer_engine {
    class FPSCounterBehaviour : public spic::BehaviourScript {
    public:
        FPSCounterBehaviour(std::string textId, std::string fontPath, int fontSize, spic::Color fontColor);

        void OnUpdate() override;

    private:
        int _lastFPS = 0;
        bool _active = true;

        const std::string _textId;
        const std::string _fontPath;
        const int _fontSize;
        const spic::Color _fontColor;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP

#ifndef PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Color.hpp"
#include "Utility/InputEnum.hpp"

namespace platformer_engine {
    class FPSCounterBehaviour : public spic::BehaviourScript {
    public:
        FPSCounterBehaviour(const std::string &textId, const std::string &fontPath, const int fontSize,
                            const spic::Color &fontColor, const KeyCode &key);

        void OnUpdate() override;

    private:
        int _lastFPS = 0;
        bool _visible = true;

        const KeyCode _key;
        const std::string _textId;
        const std::string _fontPath;
        const int _fontSize;
        const spic::Color _fontColor;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP

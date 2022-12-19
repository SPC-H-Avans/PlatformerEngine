#ifndef PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Color.hpp"
#include "Utility/InputEnum.hpp"

namespace platformer_engine {
    class FPSCounterBehaviour : public spic::BehaviourScript {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<BehaviourScript, FPSCounterBehaviour>(*this);
            boost::serialization::void_cast_register<FPSCounterBehaviour, BehaviourScript>();
            ar & _key;
            ar & _textId;
            ar & _fontPath;
            ar & _fontColor;
            ar & _fontSize;
        }

        FPSCounterBehaviour();
        FPSCounterBehaviour(std::string textId, std::string fontPath, int fontSize, spic::Color fontColor, KeyCode);

        void OnUpdate(double speedMultiplier) override;

    private:
        int _lastFPS = 0;
        bool _visible = true;

        KeyCode _key;
        std::string _textId;
        std::string _fontPath;
        int _fontSize;
        spic::Color _fontColor;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_FPSCOUNTERBEHAVIOUR_HPP

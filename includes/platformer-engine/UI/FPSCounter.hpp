#ifndef PLATFORMER_ENGINE_FPSCOUNTER_HPP
#define PLATFORMER_ENGINE_FPSCOUNTER_HPP

#include <memory>

#include "UIObject.hpp"
#include "Utility/InputEnum.hpp"

namespace platformer_engine {
    class FPSCounter {
    public:
        /**
         * @brief Constructor
         */
        FPSCounter(spic::Transform transform, std::string fontPath, int fontSize,
                   spic::Color fontColor, int width, int height, KeyCode key);

        auto GetUIObject() -> std::shared_ptr<spic::UIObject> { return _obj; }

    private:
        std::shared_ptr<spic::UIObject> _obj;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_FPSCOUNTER_HPP

#ifndef PLATFORMER_ENGINE_FPSCOUNTER_HPP
#define PLATFORMER_ENGINE_FPSCOUNTER_HPP

#include <memory>

#include "GameObject.hpp"
#include "Utility/InputEnum.hpp"

namespace platformer_engine {
    class FPSCounter {
    public:
        /**
         * @brief Constructor
         */
        FPSCounter(spic::Transform transform, std::string fontPath, int fontSize,
                   spic::Color fontColor, int width, int height, KeyCode key);

    private:
        std::shared_ptr<spic::GameObject> _obj;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_FPSCOUNTER_HPP

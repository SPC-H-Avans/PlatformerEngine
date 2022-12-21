#ifndef PLATFORMER_ENGINE_CLICKSYSTEM_HPP
#define PLATFORMER_ENGINE_CLICKSYSTEM_HPP

#include "System/ISystem.hpp"
#include <tuple>

class ClickSystem : public ISystem{

public:
    /**
     * @brief Constructor
     */
    ClickSystem(bool fullscreen);

    /**
     * @brief Check if Any Buttons should call Click()
     */
    void Update(double speedMultiplier);

private:
    auto GetRelativeMousePosition() -> std::tuple<int, int>;

    bool _fullscreen;
};

#endif //PLATFORMER_ENGINE_CLICKSYSTEM_HPP

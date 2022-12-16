#ifndef PLATFORMER_ENGINE_CLICKSYSTEM_HPP
#define PLATFORMER_ENGINE_CLICKSYSTEM_HPP

#include "System/ISystem.hpp"

class ClickSystem : public ISystem{

public:
    /**
     * @brief Check if Any Buttons should call Click()
     */
    void Update();
};

#endif //PLATFORMER_ENGINE_CLICKSYSTEM_HPP

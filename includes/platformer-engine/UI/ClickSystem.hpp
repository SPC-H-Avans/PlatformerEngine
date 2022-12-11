#ifndef PLATFORMER_ENGINE_CLICKSYSTEM_HPP
#define PLATFORMER_ENGINE_CLICKSYSTEM_HPP

class ClickSystem {

public:
    /**
     * @brief Check if Any Buttons should call Click()
     */
    static void Update(double deltaTime);
};

#endif //PLATFORMER_ENGINE_CLICKSYSTEM_HPP

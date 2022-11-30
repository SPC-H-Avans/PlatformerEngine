#ifndef PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace platformer_engine {

    class PlayerInputBehaviour : public spic::BehaviourScript {
    public:
        void OnUpdate() override;
    private:
    };

}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP

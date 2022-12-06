#ifndef PLATFORMER_ENGINE_DODGEOBJECTSBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_DODGEOBJECTSBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace platformer_engine {

    class DodgeObjectsBehaviour : public spic::BehaviourScript {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnTriggerEnter2D(Collision collision) override;
    };

}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_DODGEOBJECTSBEHAVIOUR_HPP

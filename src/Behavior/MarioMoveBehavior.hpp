#ifndef PLATFORMER_ENGINE_MARIOMOVEBEHAVIOR_HPP
#define PLATFORMER_ENGINE_MARIOMOVEBEHAVIOR_HPP

#include "BehaviourScript.hpp"

namespace platformer_engine {

    class MarioMoveBehavior : public spic::BehaviourScript {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnTriggerEnter2D(const Collision collision) override;
        void OnTriggerExit2D(const Collision collision) override;
        void OnTriggerStay2D(const Collision collision) override;
    };

} // platformer_engine

#endif //PLATFORMER_ENGINE_MARIOMOVEBEHAVIOR_HPP

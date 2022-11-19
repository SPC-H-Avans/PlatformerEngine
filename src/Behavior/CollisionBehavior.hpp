#ifndef PLATFORMER_ENGINE_COLLISIONBEHAVIOR_HPP
#define PLATFORMER_ENGINE_COLLISIONBEHAVIOR_HPP

#include "BehaviourScript.hpp"

namespace platformer_engine {

    class CollisionBehavior : public spic::BehaviourScript {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnTriggerEnter2D(const Collision collision) override;
        void OnTriggerExit2D(const Collision collision) override;
        void OnTriggerStay2D(const Collision collision) override;
    };

} // platformer_engine

#endif //PLATFORMER_ENGINE_COLLISIONBEHAVIOR_HPP

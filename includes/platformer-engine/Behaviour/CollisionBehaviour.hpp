#ifndef PLATFORMER_ENGINE_COLLISIONBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_COLLISIONBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace platformer_engine {

    class CollisionBehaviour : public spic::BehaviourScript {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnTriggerEnter2D(Collision collision) override;
        void OnTriggerExit2D(Collision collision) override;
        void OnTriggerStay2D(Collision collision) override;
    private:
        std::vector<Collision> _activeCollisions;

        void UpdateMoveRestriction(const Collision &col, bool allow);
    };

} // platformer_engine

#endif //PLATFORMER_ENGINE_COLLISIONBEHAVIOUR_HPP

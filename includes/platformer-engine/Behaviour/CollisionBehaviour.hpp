#ifndef PLATFORMER_ENGINE_COLLISIONBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_COLLISIONBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

namespace platformer_engine {

    class CollisionBehaviour : public spic::BehaviourScript {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<BehaviourScript, CollisionBehaviour>(*this);
            boost::serialization::void_cast_register<CollisionBehaviour, BehaviourScript>();
        }

        void OnStart() override;

        void OnUpdate(double speedMultiplier) override;

        void OnTriggerEnter2D(Collision collision) override;

        void OnTriggerExit2D(Collision collision) override;

        void OnTriggerStay2D(Collision collision) override;

    private:
        std::vector<Collision> _activeCollisions;

        /**
        * @brief Update the moveRestrictions for the GameObject's rigidbody for the current collision
        */
        void UpdateMoveRestriction(Collision &col, bool allow);

        /**
        * @brief When an object has moved more than a single pixel in a tick, it can move through a block.
         * To prevent this, this unstuck function moves the GameObject to the correct location using the collisionPoint.
        */
        void Unstuck(Collision &collision);
    };

}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_COLLISIONBEHAVIOUR_HPP

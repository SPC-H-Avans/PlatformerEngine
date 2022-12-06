#include "Behaviour/DodgeObjectsBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"

namespace platformer_engine {



    /*
     * Idea behind this:
     * FDE has two colliders, one in itself that has the same location as the object and one that's in front of
     * the FDE in the direction it's heading.
     * There should be a lookahead in the FDE body that decides how far away the object is.
     * The body is responsible for updating the second collider's location.
     *
     * When a collision is detected:
     *  > Check if it was the 'main' or the 'lookahead' collider                            CHECK
     *  > if it's the lookahead collider, send it to the rigidbody as 'nearby objects'      CHECK
     *
     *  The rigidbody then uses these nearby objects to optionally provide force in the opposite direction for the
     *  most 'threatening' object.
     *
     *  Then clear the nearby objects vector
     */


    void DodgeObjectsBehaviour::OnStart() {
    }

    void DodgeObjectsBehaviour::OnUpdate() {
    }

    void DodgeObjectsBehaviour::OnTriggerEnter2D(Collision collision) {
        std::shared_ptr<GameObject> currentGameObject { GetGameObject().lock() };
        if(currentGameObject) {
            auto gameObjectLocation = currentGameObject->GetTransform().position;
            auto selfCollider = collision.GetSelfCollider();
            auto selfColliderLocation = selfCollider->GetPosition();
            if(gameObjectLocation.Equals(selfColliderLocation)) return;

            // The gameObject location is different then the collider, this means that this collider
            // is a look ahead collider.

            auto body = std::dynamic_pointer_cast<RigidBody>(currentGameObject->GetComponent<RigidBody>());
            if(body == nullptr) return;

            body->AddNearbyCollider(*collision.GetOtherCollider());

        } else {
            currentGameObject.reset();
        }
    }
}  // namespace platformer_engine
#include "Behaviour/CollisionBehaviour.hpp"
#include "Input.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"

namespace platformer_engine {

    void CollisionBehaviour::OnStart() {
    }

    void CollisionBehaviour::OnUpdate() {
    }

    void CollisionBehaviour::OnTriggerEnter2D(const Collision collision) {
        _activeCollisions.push_back(collision);
        UpdateMoveRestriction(collision, false);
    }

    void CollisionBehaviour::OnTriggerExit2D(const Collision collision) {

        // Remove the collision from _activeCollisions
        for(auto &col : _activeCollisions) {
            int currentId = col.GetId();
            if(currentId == collision.GetId()) {
                auto new_end = std::remove_if(_activeCollisions.begin(), _activeCollisions.end(),
                                              [currentId](const Collision & col) { return col.GetId() == currentId; });
                _activeCollisions.erase(new_end, _activeCollisions.end());
            }
        }
        UpdateMoveRestriction(collision, true);
    }

    void CollisionBehaviour::OnTriggerStay2D(const Collision collision) {
        //todo: Make stay for obejcts you can pass through
//        for(auto &col : _activeCollisions) {
//            if(col.GetId() == collision.GetId() && col.Contact() != collision.Contact()) {
//                UpdateMoveRestriction(col, true);
//                UpdateMoveRestriction(collision, false);
//                col.Contact(collision.Contact()); // Update the contact point (for if an object could move through another)
//                break;
//            }
//        }
    }

    void CollisionBehaviour::UpdateMoveRestriction(const Collision &col, bool allow) {
        auto points = col.Contacts();
        auto gameObjWeak = GetGameObject();
        std::shared_ptr<spic::GameObject> gameObj { gameObjWeak.lock() };
        if (gameObj) {
            auto body = std::static_pointer_cast<RigidBody>(gameObj->GetComponent<RigidBody>());
            if(body != nullptr) {
                for(auto point : points) {
                    if(allow) {
                        body->AllowMoveTo(point);
                    } else {
                        body->DenyMoveTo(point);
                    }
                }
            }
        } else { // gameObjWeak is already deleted
            gameObjWeak.reset();
        }
    }
}  // namespace platformer_engine
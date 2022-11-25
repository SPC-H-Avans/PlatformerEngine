#include "Behaviour/CollisionBehaviour.hpp"
#include "Input.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"

namespace platformer_engine {

    void CollisionBehaviour::OnStart() {
    }

    void CollisionBehaviour::OnUpdate() {
    }

    void CollisionBehaviour::OnTriggerEnter2D(const Collision collision) {
        _activeCollisions.push_back(collision);
        UpdateMoveRestriction(collision, false);
        Unstuck(collision);
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
        for(auto &col : _activeCollisions) {
            if(col.GetId() == collision.GetId() && col.Contact() != collision.Contact()) {
                UpdateMoveRestriction(col, true);
                UpdateMoveRestriction(collision, false);
                col.Contact(collision.Contact()); // Update the contact point (for if an object could move through another)
                break;
            }
        }
    }

    void CollisionBehaviour::UpdateMoveRestriction(const Collision &col, bool allow) {
        auto point = col.Contact();
        auto gameObjWeak = GetGameObject();
        std::shared_ptr<spic::GameObject> gameObj { gameObjWeak.lock() };
        if (gameObj) {
            auto body = std::static_pointer_cast<RigidBody>(gameObj->GetComponent<RigidBody>());
            if(body != nullptr) {
                if(allow) {
                    body->AllowMoveTo(point);
                } else {
                    body->DenyMoveTo(point);
                }
            }
        } else { // gameObjWeak is already deleted
            gameObjWeak.reset();
        }
    }

    void CollisionBehaviour::Unstuck(const Collision &collision) {
        std::shared_ptr<GameObject> dyn_gob { GetGameObject().lock() };
        if(dyn_gob) {
            auto dyn_transform = dyn_gob->GetTransform();
            auto dyn_col = std::dynamic_pointer_cast<BoxCollider>(dyn_gob->GetComponent<BoxCollider>());

            auto stat_gob = collision.GetCollider()->GetGameObject().lock();
            if(stat_gob) {
                auto stat_transform = stat_gob->GetTransform();
                auto stat_col = std::dynamic_pointer_cast<BoxCollider>(collision.GetCollider());

                if(collision.Contact() == CollisionPoint::Top) {
                    dyn_transform.position.y = stat_transform.position.y + stat_col->Height() + 1;
                }
                else if(collision.Contact() == CollisionPoint::Bottom) {
                    dyn_transform.position.y = stat_transform.position.y - dyn_col->Height() - 1;
                }
                else if(collision.Contact() == CollisionPoint::Left) {
                    dyn_transform.position.x = stat_transform.position.x + stat_col->Width() + 1;
                }
                else if(collision.Contact() == CollisionPoint::Right) {
                    dyn_transform.position.x = stat_transform.position.x - dyn_col->Width() - 1;
                }
            } else {
                stat_gob.reset();
            }
        } else {
            dyn_gob.reset();
        }
    }
}  // namespace platformer_engine
#include "Behaviour/CollisionBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Engine/Engine.hpp"

namespace platformer_engine {

    void CollisionBehaviour::OnStart() {
    }

    void CollisionBehaviour::OnUpdate() {
    }

    void CollisionBehaviour::OnTriggerEnter2D(Collision collision) {
        _activeCollisions.push_back(collision);
        UpdateMoveRestriction(collision, false);
        Unstuck(collision);
    }

    void CollisionBehaviour::OnTriggerExit2D(Collision collision) {

        // Remove the collision from _activeCollisions
        for (auto &col: _activeCollisions) {
            int currentId = col.GetId();
            if (currentId == collision.GetId()) {
                auto newEnd = std::remove_if(_activeCollisions.begin(), _activeCollisions.end(),
                                             [currentId](const Collision &col) { return col.GetId() == currentId; });
                _activeCollisions.erase(newEnd, _activeCollisions.end());
            }
        }
        UpdateMoveRestriction(collision, true);
    }

    void CollisionBehaviour::OnTriggerStay2D(Collision collision) {
    }

    void CollisionBehaviour::UpdateMoveRestriction(Collision &col, bool allow) {
        if (!col.GetCollider()->GetObstructsMovement()) return;
        auto point = col.Contact();
        auto gameObjWeak = GetGameObject();
        std::shared_ptr<spic::GameObject> gameObj{gameObjWeak.lock()};
        if (gameObj) {
            auto body = std::static_pointer_cast<RigidBody>(gameObj->GetComponent<RigidBody>());
            if (body != nullptr) {
                if (allow) {
                    body->AllowMoveTo(point);
                } else {
                    body->DenyMoveTo(point);
                }
            }
        } else { // gameObjWeak is already deleted
            gameObjWeak.reset();
        }
    }

    void CollisionBehaviour::Unstuck(Collision &collision) {
        std::shared_ptr<GameObject> currentGameObject{GetGameObject().lock()};
        if (currentGameObject &&
            currentGameObject->GetOwnerId() == platformer_engine::Engine::GetInstance().GetLocalClientId()) {
            auto currentTransform = currentGameObject->GetTransform();
            auto currentCollider = std::dynamic_pointer_cast<BoxCollider>(
                    currentGameObject->GetComponent<BoxCollider>());

            auto collidingGameObject = collision.GetCollider()->GetGameObject().lock();
            if (collidingGameObject) {
                auto collidingTransform = collidingGameObject->GetTransform();
                auto collidingCollider = std::dynamic_pointer_cast<BoxCollider>(collision.GetCollider());

                if (collision.Contact() == CollisionPoint::Top) {
                    currentTransform.position.y = collidingTransform.position.y + collidingCollider->Height();
                } else if (collision.Contact() == CollisionPoint::Bottom) {
                    currentTransform.position.y = collidingTransform.position.y - currentCollider->Height();
                } else if (collision.Contact() == CollisionPoint::Left) {
                    currentTransform.position.x = collidingTransform.position.x + collidingCollider->Width();
                } else if (collision.Contact() == CollisionPoint::Right) {
                    currentTransform.position.x = collidingTransform.position.x - currentCollider->Width();
                }
                currentGameObject->SetTransform(currentTransform);
            } else {
                collidingGameObject.reset();
            }
        } else {
            currentGameObject.reset();
        }
    }
}  // namespace platformer_engine
BOOST_CLASS_EXPORT(platformer_engine::CollisionBehaviour);